#include "MeshComponent.h"
#include "MeshData.h"

namespace sre
{

IMPLEMENT_COMPONENT(MeshComponent)

MeshComponent::MeshComponent(Entity *entity, MeshData* meshData)
    : ARenderableComponent(entity)
{
	this->meshData = UPTR<MeshData>{ meshData };
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

} // namespace
