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

	this->material = std::make_unique<Material>();	// compila o shader

	RenderManager::getInstance()->createVBO(this);
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
*/

void MeshComponent::setMaterial(UPTR<Material> &material)
{
	this->material = std::move(material);
}

void MeshComponent::setReceiveLight(bool receiveLight)
{
	this->receiveLight = receiveLight;
}

} // namespace
