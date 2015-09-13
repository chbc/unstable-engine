#include "RenderableNode.h"
#include <engine/systems/graphics/LightManager.h>

namespace nodes
{

RenderableNode::RenderableNode() : Node()
{
	this->receiveLight = true;
}

RenderableNode::~RenderableNode()
{
    Mesh *mesh = NULL;
    for (unsigned int i = 0; i < this->meshes.size(); i++)
    {
        mesh = this->meshes[i];
        if (mesh != NULL)
            delete mesh;
    }

    this->meshes.clear();
}

void RenderableNode::setMaterial(Material *material, unsigned int meshIndex)
{
    if ((meshIndex >= 0) && (meshIndex < this->meshes.size()))
        this->meshes[meshIndex]->setMaterial(material);
    // else TODO: log error
}

void RenderableNode::setReceiveLight(bool receiveLight)
{
	this->receiveLight = receiveLight;
}

} // namespace nodes
