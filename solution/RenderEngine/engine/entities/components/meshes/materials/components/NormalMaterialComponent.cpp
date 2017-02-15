#include "NormalMaterialComponent.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

NormalMaterialComponent::NormalMaterialComponent(Material *material, const std::string &fileName)
	: AMaterialComponent(material)
{
	this->loadTexture(fileName);
}

void NormalMaterialComponent::loadTexture(const std::string &fileName)
{
	Texture *newTexture = RenderManager::getInstance()->loadNormalTexture(fileName);
	this->texture = UPTR<Texture>{ newTexture };
}

uint32_t NormalMaterialComponent::getTextureID()
{
	return this->texture->getId();
}

} // namespace
