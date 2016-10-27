#ifndef MODELNODE_H
#define MODELNODE_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "RenderableNode.h"

namespace nodes
{

class ModelNode : public RenderableNode
{
    private:
        void recursiveProcess(aiNode *node, const aiScene *scene);
        void processMesh(aiMesh *mesh, const aiScene *scene);

    public:
        ModelNode(SceneManager *sceneManager, const char *fileName);
        ~ModelNode();
};

} // namespace nodes

#endif // MODELNODE_H
