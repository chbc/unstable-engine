#pragma once

#include <string>
#include "MeshData.h"
#include "memory_aliases.h"
#include "ModelImportData.h"

#include "assimp/matrix4x4.h"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
enum aiTextureType;

namespace sre
{

class ModelLoader
{
public:
    void load(const char* filePath, float scaleFactor, bool importMaterial, ModelImportData& result);

private:
    void processNode(const aiScene *scene, aiNode* node, aiMatrix4x4& parentTransform, ModelImportData& result);
    MeshData processMesh(aiMesh *inputMesh, aiMatrix4x4& nodeTransform);
	void processMaterials(const aiScene* scene, const std::string& basePath, ModelImportData& result);
	void checkAndAddTexturePath(aiMaterial* inputMaterial, const std::string& basePath,
        aiTextureType aiTextureType, ETextureMap::Type textureMap, MaterialImportData& result);
    glm::mat4 AssimpToGLM(const aiMatrix4x4& ai_mat);

friend class Scene;
};

} // namespace
