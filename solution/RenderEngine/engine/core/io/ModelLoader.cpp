#include "ModelLoader.h"
#include <engine/entities/Entity.h>
#include <engine/entities/components/meshes/MeshComponent.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace sre
{

Entity *ModelLoader::load(const std::string &fileName)
{
	Entity *rootEntity = nullptr;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals); 

	if
	(
		(scene == nullptr) || 
		(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || 
		(scene->mRootNode == nullptr)
	)
		throw "[ModelLoader] - Load Error: " + std::string(importer.GetErrorString());

	this->directory = fileName.substr(0, fileName.find_last_of('/')) + '/';
	rootEntity = this->processNode(scene->mRootNode, scene);

	return rootEntity;
}

Entity *ModelLoader::processNode(aiNode *node, const aiScene *scene)
{
	Entity *newEntity = new Entity;

	for(uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->processMesh(mesh, scene, newEntity);
	}
	
	for(uint32_t i = 0; i < node->mNumChildren; i++)
	{
		Entity *childEntity = this->processNode(node->mChildren[i], scene);
		newEntity->addChild(childEntity);
	}

	return newEntity;
}

void ModelLoader::processMesh(aiMesh *inputMesh, const aiScene *scene, Entity *entity)
{
	VECTOR_UPTR<VertexData> vertexData;
	VertexData *newData = nullptr;

	for(uint32_t i = 0; i < inputMesh->mNumVertices; i++)
	{
		newData = new VertexData;
		newData->position = glm::vec3(inputMesh->mVertices[i].x, inputMesh->mVertices[i].y, inputMesh->mVertices[i].z);
		newData->normal = glm::vec3(inputMesh->mNormals[i].x, inputMesh->mNormals[i].y, inputMesh->mNormals[i].z);

		if (inputMesh->mTextureCoords[0])
		{
			newData->u = inputMesh->mTextureCoords[0][i].x;
			newData->v = inputMesh->mTextureCoords[0][i].y;
		}

		vertexData.emplace_back(newData);
	}

	std::vector<uint32_t> indices;
	for(uint32_t i = 0; i < inputMesh->mNumFaces; i++)
	{
		aiFace face = inputMesh->mFaces[i];
		for(uint32_t j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	UPTR<MeshData<VertexData>> objectData = std::make_unique<MeshData<VertexData>>(vertexData, indices);

	MeshComponent *entityMesh = entity->addComponent<MeshComponent>(objectData);
	this->processMaterials(inputMesh, scene, entityMesh);
}

void ModelLoader::processMaterials(aiMesh *inputMesh, const aiScene *scene, MeshComponent *entityMesh)
{
	if(inputMesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[inputMesh->mMaterialIndex];
		aiString fileName;
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			material->GetTexture(aiTextureType_DIFFUSE, 0, &fileName);
			entityMesh->addMaterialComponent<DiffuseMaterialComponent>(this->directory + fileName.C_Str());
		}

		if (material->GetTextureCount(aiTextureType_NORMALS) > 0)
		{
			material->GetTexture(aiTextureType_NORMALS, 0, &fileName);
			entityMesh->addMaterialComponent<NormalMaterialComponent>(this->directory + fileName.C_Str());
		}

		if (material->GetTextureCount(aiTextureType_SPECULAR) > 0)
		{
			material->GetTexture(aiTextureType_SPECULAR, 0, &fileName);
			entityMesh->addMaterialComponent<SpecularMaterialComponent>(this->directory + fileName.C_Str());
		}

		if (material->GetTextureCount(aiTextureType_AMBIENT) > 0)
		{
			material->GetTexture(aiTextureType_AMBIENT, 0, &fileName);
			entityMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>(this->directory + fileName.C_Str());
		}
	}
}

} // namespace
