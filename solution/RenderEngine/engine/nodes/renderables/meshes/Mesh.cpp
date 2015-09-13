#include "Mesh.h"
#include <engine/systems/graphics/RenderManager.h>
#include <engine/nodes/renderables/materials/ColorMaterial.h>

namespace nodes
{

Mesh::Mesh(std::vector<VertexData> *vertexData, std::vector<unsigned int> *indices)
{
    this->vertexData = vertexData;
    this->indices = indices;

	this->material = new ColorMaterial;

	this->renderManager = RenderManager::getInstance();
	this->renderManager->createBufferObject(this);
}

Mesh::~Mesh()
{
    this->vertexData->clear();
    delete this->vertexData;

    this->indices->clear();
    delete this->indices;

	delete this->material;
}

void Mesh::applyMaterial(bool receiveLight)
{
    this->material->apply(this->vertexData, receiveLight);
}

void Mesh::setMaterial(Material *material)
{
    delete this->material;
	this->material = material;
}

} // namespace nodes
