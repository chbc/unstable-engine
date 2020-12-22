#include "NormalMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"

namespace sre
{

NormalMaterialComponent::NormalMaterialComponent(Material *material, const std::string &fileName)
	: AMaterialComponent(material)
{
	this->texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadTexture(fileName, EMaterialMap::NORMAL);
}

uint32_t NormalMaterialComponent::getTextureID() const
{
	return this->texture->getId();
}

} // namespace
