#include "SpecularMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"

namespace sre
{
SpecularMaterialComponent::SpecularMaterialComponent(Material *material, const std::string &fileName)
	: AMaterialComponent(material)
{
	this->texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadTexture(fileName, EMaterialMap::SPECULAR);
}

uint32_t SpecularMaterialComponent::getTextureID(uint32_t index) const
{
	return this->texture->getId();
}

} // namespace
