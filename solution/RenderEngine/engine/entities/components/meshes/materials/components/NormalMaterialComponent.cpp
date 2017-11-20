#include "NormalMaterialComponent.h"
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

NormalMaterialComponent::NormalMaterialComponent(Material *material, const std::string &fileName)
	: AMaterialComponent(material)
{
	this->loadTexture(fileName);
}

void NormalMaterialComponent::loadTexture(const std::string &fileName)
{
	Texture *newTexture = SingletonsManager::getInstance()->resolve<RenderManager>()->loadNormalTexture(fileName);
	this->texture = UPTR<Texture>{ newTexture };
}

uint32_t NormalMaterialComponent::getTextureID()
{
	return this->texture->getId();
}

} // namespace
