#include "SpriteMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"

namespace sre
{

SpriteMaterialComponent::SpriteMaterialComponent(Material* material, const std::string& fileName)
	: AMaterialComponent(material)
{
	this->texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadTexture(fileName, EMaterialMap::GUI);
}

uint32_t SpriteMaterialComponent::getTextureID() const
{
	return this->texture->getId();
}

} // namespace
