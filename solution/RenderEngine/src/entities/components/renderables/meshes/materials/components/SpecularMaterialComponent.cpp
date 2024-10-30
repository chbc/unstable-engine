#include "SpecularMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(SpecularMaterialComponent)

SpecularMaterialComponent::SpecularMaterialComponent(Material *material, const std::string &fileName)
	: AMaterialComponent(material)
{
	this->texture = SingletonsManager::getInstance()->get<TextureManager>()->loadTexture(fileName, EMaterialMap::SPECULAR);
	this->addEditorProperty(new TextureEditorProperty{ "Specular", this->texture->getId() });
}

uint32_t SpecularMaterialComponent::getTextureID(uint32_t index) const
{
	return this->texture->getId();
}

} // namespace
