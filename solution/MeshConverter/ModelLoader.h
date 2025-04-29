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
    void processNode(const aiScene *scene, const aiMatrix4x4& nodeTransform, aiNode* node, std::vector<MeshData>& result);
    MeshData processMesh(const aiMatrix4x4& nodeTransform, aiMesh *inputMesh);

friend class Scene;
};

} // namespace
