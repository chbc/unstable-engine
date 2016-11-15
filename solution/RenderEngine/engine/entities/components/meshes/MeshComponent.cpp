#include "MeshComponent.h"
#include <engine/systems/graphics/RenderManager.h>
#include <engine/entities/components/meshes/materials/ColorMaterial.h>

namespace sre
{

MeshComponent::MeshComponent(Entity *entity, VECTOR_UPTR<VertexData> &vertexData, VECTOR_UPTR<uint32_t> &indices)  
	: AEntityComponent(entity)
{
	this->vertexData = std::move(vertexData);
	this->indices = std::move(indices);

	// ### this->material = std::make_unique<ColorMaterial>();

	RenderManager::getInstance()->createBufferObject(this);
}

MeshComponent::~MeshComponent()
{
    this->vertexData.clear();
    this->indices.clear();
}

/* ###
void MeshComponent::applyMaterial(bool receiveLight)
{
    this->material->apply(this->vertexData, receiveLight);
}

void MeshComponent::setMaterial(Material *material)
{
	this->material.reset(material);
}

void MeshComponent::setMaterial(UPTR<Material> &material)
{
	this->material = std::move(material);
}

void MeshComponent::setReceiveLight(bool receiveLight)
{
	this->receiveLight = receiveLight;
}
*/

} // namespace
