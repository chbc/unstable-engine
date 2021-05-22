#include "AmbientOcclusionMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(AmbientOcclusionMaterialComponent)

AmbientOcclusionMaterialComponent::AmbientOcclusionMaterialComponent(Material *material, const std::string &fileName)
	: AMaterialComponent(material)
{
	this->texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadTexture(fileName, EMaterialMap::AMBIENT_OCCLUSION);
	this->addEditorProperty(new TextureEditorProperty{ "Ambient Occlusion", this->texture->getId() });
}

uint32_t AmbientOcclusionMaterialComponent::getTextureID(uint32_t index) const
{
	return this->texture->getId();
}

} // namespace
