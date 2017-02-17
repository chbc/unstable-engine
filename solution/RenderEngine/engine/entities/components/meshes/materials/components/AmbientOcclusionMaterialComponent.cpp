#include "AmbientOcclusionMaterialComponent.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{
AmbientOcclusionMaterialComponent::AmbientOcclusionMaterialComponent(Material *material, const std::string &fileName)
	: NormalMaterialComponent(material, fileName)
{ }

void AmbientOcclusionMaterialComponent::loadTexture(const std::string &fileName)
{
	Texture *newTexture = RenderManager::getInstance()->loadAOTexture(fileName);
	this->texture = UPTR<Texture>{ newTexture };
}

} // namespace
