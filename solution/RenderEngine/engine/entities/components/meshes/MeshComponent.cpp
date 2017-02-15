#include "MeshComponent.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

MeshComponent::MeshComponent
(
	Entity *entity, 
	VECTOR_UPTR<VertexData> &vertexData, 
	std::vector<uint32_t> &indices
)
	: AEntityComponent(entity)
{
	this->vertexData = std::move(vertexData);
	this->indices = std::move(indices);

	this->material = UPTR<Material>{ new Material{} };
}

MeshComponent::~MeshComponent()
{
    this->vertexData.clear();
    this->indices.clear();
}

Material *MeshComponent::getMaterial()
{
	return this->material.get();
}

void MeshComponent::setMaterial(UPTR<Material> &material)
{
	this->material = std::move(material);
}

void MeshComponent::setReceiveLight(bool receiveLight)
{
	this->receiveLight = receiveLight;
}

void MeshComponent::notifyBeforeMaterialChange()
{
	RenderManager::getInstance()->onBeforeMaterialChange(this);
}

void MeshComponent::notifyAfterMaterialChange()
{
	RenderManager::getInstance()->onAfterMaterialChange(this);
}

} // namespace
