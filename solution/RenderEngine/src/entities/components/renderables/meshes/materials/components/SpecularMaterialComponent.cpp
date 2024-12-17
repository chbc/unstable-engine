#include "SpecularMaterialComponent.h"
#include "Texture.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(SpecularMaterialComponent, SPECULAR_MATERIAL)

SpecularMaterialComponent::SpecularMaterialComponent(Material *material)
	: ABaseTextureMaterialComponent(material)
{
	this->addEditorProperty(new TextureEditorProperty{ "Specular", &this->texture->getId() });
}

ETextureMap::Type SpecularMaterialComponent::getTextureType()
{
	return ETextureMap::SPECULAR;
}

} // namespace
