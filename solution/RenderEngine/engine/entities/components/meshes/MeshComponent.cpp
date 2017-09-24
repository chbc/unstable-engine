#include "MeshComponent.h"
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

MeshComponent::MeshComponent(Entity *entity, UPTR<MeshData<VertexData>> &objectData)
	: AEntityComponent(entity)
{
	this->objectData = std::move(objectData);
	this->material = UPTR<Material>{ new Material{} };
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

} // namespace
