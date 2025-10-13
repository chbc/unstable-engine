#include "SpecularMaterialComponent.h"
#include "Texture.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(SpecularMaterialComponent, SPECULAR_MATERIAL)

SpecularMaterialComponent::SpecularMaterialComponent(ABaseMaterial *material)
	: ABaseTextureMaterialComponent(material)
{
	this->addEditorProperty(new TextureEditorProperty{ "Specular", &this->texture, ETextureMap::SPECULAR });
}

} // namespace
