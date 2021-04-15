#include "ModelLoader.h"
#include "Entity.h"
#include "MeshComponent.h"
#include "MeshData.h"

#ifndef __ANDROID__
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

namespace sre
{

void ModelLoader::load(Entity *rootEntity, const std::string &fileName)
{
#ifndef __ANDROID__
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile
	(
		fileName, 
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_CalcTangentSpace
	);

    if
    (
        (scene == nullptr) || 
        (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || 
        (scene->mRootNode == nullptr)
    )
        throw "[ModelLoader] - Load Error: " + std::string(importer.GetErrorString());

    this->directory = fileName.substr(0, fileName.find_last_of('/')) + '/';
    this->processNode(rootEntity, scene->mRootNode, scene);
#endif
}

void ModelLoader::processNode(Entity *entity, aiNode *node, const aiScene *scene)
{
#ifndef __ANDROID__
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->processMesh(mesh, scene, entity);
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        Entity *childEntity = new Entity;
        this->processNode(childEntity, node->mChildren[i], scene);
        entity->addChild(childEntity, node->mChildren[i]->mName.C_Str());
        childEntity->onStart();
    }
#endif
}

void ModelLoader::processMesh(aiMesh *inputMesh, const aiScene *scene, Entity *entity)
{
#ifndef __ANDROID__
	std::vector<VertexData> vertexData;
	for(uint32_t i = 0; i < inputMesh->mNumVertices; i++)
	{
		VertexData newData;
		newData.position = glm::vec3(inputMesh->mVertices[i].x, inputMesh->mVertices[i].y, inputMesh->mVertices[i].z);
		newData.normal = glm::vec3(inputMesh->mNormals[i].x, inputMesh->mNormals[i].y, inputMesh->mNormals[i].z);

		if (inputMesh->mTextureCoords[0])
		{
			newData.u = inputMesh->mTextureCoords[0][i].x;
			newData.v = inputMesh->mTextureCoords[0][i].y;
		}

		if ((inputMesh->mTangents != nullptr) && (inputMesh->mBitangents != nullptr))
		{
			newData.tangent = glm::vec3(inputMesh->mTangents[i].x, inputMesh->mTangents[i].y, inputMesh->mTangents[i].z);
			newData.bitangent = glm::vec3(inputMesh->mBitangents[i].x, inputMesh->mBitangents[i].y, inputMesh->mBitangents[i].z);
		}

		vertexData.emplace_back(newData);
	}

	std::vector<uint16_t> indices;
	for(uint32_t i = 0; i < inputMesh->mNumFaces; i++)
	{
		aiFace face = inputMesh->mFaces[i];
		for(uint32_t j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	MeshData* objectData = new MeshData{ vertexData, indices };
	MeshComponent *entityMesh = entity->addComponent<MeshComponent>(objectData);
	this->processMaterials(inputMesh, scene, entityMesh);
#endif
}

void ModelLoader::processMaterials(aiMesh *inputMesh, const aiScene *scene, MeshComponent *entityMesh)
{
#ifndef __ANDROID__
	if(inputMesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[inputMesh->mMaterialIndex];
		aiString fileName;
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			material->GetTexture(aiTextureType_DIFFUSE, 0, &fileName);
			entityMesh->addMaterialComponent<DiffuseMaterialComponent>(this->directory + fileName.C_Str());
		}

		/*
		if (material->GetTextureCount(aiTextureType_NORMALS) > 0)
		{
			material->GetTexture(aiTextureType_NORMALS, 0, &fileName);
			entityMesh->addMaterialComponent<NormalMaterialComponent>(this->directory + fileName.C_Str());
		}
		*/

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

		if (material->GetTextureCount(aiTextureType_HEIGHT) > 0)
		{
			material->GetTexture(aiTextureType_HEIGHT, 0, &fileName);
			entityMesh->addMaterialComponent<NormalMaterialComponent>(this->directory + fileName.C_Str());
		}

		if (material->GetTextureCount(aiTextureType_DISPLACEMENT) > 0)
		{
			material->GetTexture(aiTextureType_DISPLACEMENT, 0, &fileName);
			entityMesh->addMaterialComponent<NormalMaterialComponent>(this->directory + fileName.C_Str());
		}
	}
#endif
}

} // namespace
