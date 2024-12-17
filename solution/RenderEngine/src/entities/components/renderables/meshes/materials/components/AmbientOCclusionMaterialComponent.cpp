#include "AmbientOcclusionMaterialComponent.h"
#include "Texture.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(AmbientOcclusionMaterialComponent, AO_MATERIAL)

AmbientOcclusionMaterialComponent::AmbientOcclusionMaterialComponent(Material *material)
	: ABaseTextureMaterialComponent(material)
{
	this->addEditorProperty(new TextureEditorProperty{ "Ambient Occlusion", &this->texture->getId() });
}

ETextureMap::Type AmbientOcclusionMaterialComponent::getTextureType()
{
	return ETextureMap::AMBIENT_OCCLUSION;
}

} // namespace
