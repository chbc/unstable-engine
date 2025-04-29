#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fstream>

namespace sre
{

void ModelLoader::load(const char* fileName, std::vector<MeshData>& result)
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

	aiMatrix4x4 transform = scene->mRootNode->mTransformation;
    processNode(scene, transform, scene->mRootNode, result);
}

void ModelLoader::processNode(const aiScene* scene, const aiMatrix4x4& nodeTransform, aiNode *node, std::vector<MeshData>& result)
{
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        MeshData newMesh = processMesh(nodeTransform, mesh);
		result.emplace_back(newMesh);
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
		aiNode* childNode = node->mChildren[i];
		aiMatrix4x4 childTransform = nodeTransform * childNode->mTransformation;
        processNode(scene, childTransform, childNode, result);
    }
}

MeshData ModelLoader::processMesh(const aiMatrix4x4& nodeTransform, aiMesh* inputMesh)
{
	std::vector<VertexData> vertexData;
	for(uint32_t i = 0; i < inputMesh->mNumVertices; i++)
	{
		VertexData newData;
		aiVector3D transformedPos = nodeTransform * inputMesh->mVertices[i];
		aiVector3D transformedNormal = nodeTransform * inputMesh->mNormals[i];
		newData.position = glm::vec3(transformedPos.x, transformedPos.y, transformedPos.z);
		newData.normal = glm::vec3(transformedNormal.x, transformedNormal.y, transformedNormal.z);

		if (inputMesh->mTextureCoords[0])
		{
			newData.u = inputMesh->mTextureCoords[0][i].x;
			newData.v = inputMesh->mTextureCoords[0][i].y;
		}

		if ((inputMesh->mTangents != nullptr) && (inputMesh->mBitangents != nullptr))
		{
			aiVector3D transformedTangent = nodeTransform * inputMesh->mTangents[i];
			aiVector3D transformedBitangent = nodeTransform * inputMesh->mBitangents[i];
			newData.tangent = glm::vec3(transformedTangent.x, transformedTangent.y, transformedTangent.z);
			newData.bitangent = glm::vec3(transformedBitangent.x, transformedBitangent.y, transformedBitangent.z);
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

	return MeshData{ vertexData, indices };
}

} // namespace
