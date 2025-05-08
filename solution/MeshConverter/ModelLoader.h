#pragma once

#include <string>
#include "MeshData.h"
#include "memory_aliases.h"

#include "assimp/matrix4x4.h"

struct aiNode;
struct aiScene;
struct aiMesh;

namespace sre
{

class ModelLoader
{
public:
    void load(const char* fileName, std::vector<MeshData>& result);

private:
    void processNode(const aiScene *scene, aiNode* node, aiMatrix4x4& parentTransform, std::vector<MeshData>& result);
    MeshData processMesh(aiMesh *inputMesh, aiMatrix4x4& nodeTransform);
    glm::mat4 AssimpToGLM(const aiMatrix4x4& ai_mat);

friend class Scene;
};

} // namespace
