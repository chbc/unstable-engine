#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fstream>

namespace sre
{

void ModelLoader::load(const char* fileName, std::vector<UPTR<MeshData>>& result)
{
	std::ifstream fin(fileName);
	if (fin.fail())
	{
		throw "[ModelLoader] - Couldn't open file: " + std::string{ fileName };
	}
	fin.close();

    Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcessPreset_TargetRealtime_Quality | aiProcess_FlipUVs);

    if
    (
        (scene == nullptr) || 
        (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || 
        (scene->mRootNode == nullptr)
    )
	{
		throw "[ModelLoader] - Load Error: " + std::string(importer.GetErrorString());
	}

	aiMatrix4x4 transform;
    processNode(scene, transform, scene->mRootNode, result);
}

void ModelLoader::processNode(const aiScene* scene, aiMatrix4x4& transform, aiNode *node, std::vector<UPTR<MeshData>>& result)
{
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        MeshData* newMesh = processMesh(transform, mesh);
		result.emplace_back(newMesh);
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
		aiNode* childNode = node->mChildren[i];
		transform = transform * childNode->mTransformation;
        processNode(scene, transform, childNode, result);
    }
}

MeshData* ModelLoader::processMesh(aiMatrix4x4& transform, aiMesh* inputMesh)
{
	std::vector<VertexData> vertexData;
	for(uint32_t i = 0; i < inputMesh->mNumVertices; i++)
	{
		VertexData newData;
		aiVector3D transformedPos = transform * inputMesh->mVertices[i];
		aiVector3D transformedNormal = transform * inputMesh->mNormals[i];
		newData.position = glm::vec3(transformedPos.x, transformedPos.y, transformedPos.z);
		newData.normal = glm::vec3(transformedNormal.x, transformedNormal.y, transformedNormal.z);

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

	std::vector<uint32_t> indices;
	for (uint32_t i = 0; i < inputMesh->mNumFaces; i++)
	{
		const aiFace& face = inputMesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return new MeshData{ vertexData, indices };
}

} // namespace
