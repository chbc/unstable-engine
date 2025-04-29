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
    void processNode(const aiScene *scene, aiMatrix4x4& transform, aiNode* node, std::vector<MeshData>& result);
    MeshData processMesh(aiMatrix4x4& transform, aiMesh *inputMesh);

friend class Scene;
};

} // namespace
