#include "AmbientOcclusionMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"

namespace sre
{
AmbientOcclusionMaterialComponent::AmbientOcclusionMaterialComponent(Material *material, const std::string &fileName)
	: AMaterialComponent(material)
{
	this->texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadTexture(fileName, EMaterialMap::AMBIENT_OCCLUSION);
}

uint32_t AmbientOcclusionMaterialComponent::getTextureID(uint32_t index) const
{
	return this->texture->getId();
}

} // namespace
