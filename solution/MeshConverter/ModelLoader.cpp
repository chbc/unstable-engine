#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <fstream>

namespace sre
{

void ModelLoader::load(const char* fileName, float scaleFactor, std::vector<MeshData>& result)
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

	aiMatrix4x4 initialTransform = aiMatrix4x4{} * scaleFactor;
    processNode(scene, scene->mRootNode, initialTransform, result);
}

void ModelLoader::processNode(const aiScene* scene, aiNode *node, aiMatrix4x4& parentTransform, std::vector<MeshData>& result)
{
    for (uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* inputMesh = scene->mMeshes[node->mMeshes[i]];
		aiMatrix4x4 meshTransform = parentTransform * node->mTransformation;
		MeshData newMesh = processMesh(inputMesh, meshTransform);
		result.emplace_back(newMesh);
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++)
    {
		aiMatrix4x4 nodeTransform = parentTransform * node->mTransformation;
        processNode(scene, node->mChildren[i], nodeTransform, result);
    }
}

MeshData ModelLoader::processMesh(aiMesh* inputMesh, aiMatrix4x4& nodeTransform)
{
	std::vector<VertexData> vertexData;
	for (uint32_t i = 0; i < inputMesh->mNumVertices; i++)
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

	MeshData result{ inputMesh->mName.C_Str(), vertexData, indices };
	return result;
}

glm::mat4 ModelLoader::AssimpToGLM(const aiMatrix4x4& ai_mat)
{
	glm::mat4 glm_mat;
	glm_mat[0][0] = ai_mat.a1; glm_mat[1][0] = ai_mat.b1; glm_mat[2][0] = ai_mat.c1; glm_mat[3][0] = ai_mat.d1;
	glm_mat[0][1] = ai_mat.a2; glm_mat[1][1] = ai_mat.b2; glm_mat[2][1] = ai_mat.c2; glm_mat[3][1] = ai_mat.d2;
	glm_mat[0][2] = ai_mat.a3; glm_mat[1][2] = ai_mat.b3; glm_mat[2][2] = ai_mat.c3; glm_mat[3][2] = ai_mat.d3;
	glm_mat[0][3] = ai_mat.a4; glm_mat[1][3] = ai_mat.b4; glm_mat[2][3] = ai_mat.c4; glm_mat[3][3] = ai_mat.d4;
	return glm_mat;
}

} // namespace
