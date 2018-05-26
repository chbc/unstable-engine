#include "MeshComponent.h"
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

MeshComponent::MeshComponent(Entity *entity, UPTR<MeshData<VertexData>> &meshData)
    : ARenderableComponent(entity)
{
    this->meshData = std::move(meshData);
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
