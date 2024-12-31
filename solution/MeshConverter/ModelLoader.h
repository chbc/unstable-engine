#pragma once

#include <string>
#include "MeshData.h"
#include "memory_aliases.h"

struct aiNode;
struct aiScene;
struct aiMesh;

namespace sre
{


class ModelLoader
{
public:
    void load(const char* fileName, std::vector<UPTR<MeshData>>& result);

private:
    void processNode(const aiScene *scene, aiNode* node, std::vector<UPTR<MeshData>>& result);
    MeshData* processMesh(const aiScene* scene, aiMesh *inputMesh);

friend class Scene;
};

} // namespace
