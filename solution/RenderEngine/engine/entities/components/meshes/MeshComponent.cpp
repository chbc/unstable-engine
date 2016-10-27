#include "MeshComponent.h"
#include <engine/systems/graphics/RenderManager.h>
#include <engine/entities/components/meshes/materials/ColorMaterial.h>

namespace sre
{

MeshComponent::MeshComponent(std::vector<VertexData> *vertexData, std::vector<unsigned int> *indices)
{
	this->vertexData = vertexData;
	this->indices = indices;

	this->material = std::make_unique<ColorMaterial>();

	RenderManager *renderManager = RenderManager::getInstance();
	renderManager->createBufferObject(this);
}

MeshComponent::~MeshComponent()
{
    this->vertexData->clear();
    delete this->vertexData;

    this->indices->clear();
    delete this->indices;
}

void MeshComponent::applyMaterial(bool receiveLight)
{
    this->material->apply(this->vertexData, receiveLight);
}

void MeshComponent::setMaterial(Material *material)
{
	this->material.reset(material);
}

void MeshComponent::setReceiveLight(bool receiveLight)
{
	this->receiveLight = receiveLight;
}

} // namespace
