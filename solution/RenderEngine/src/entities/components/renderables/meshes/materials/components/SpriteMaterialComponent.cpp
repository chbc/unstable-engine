#include "SpriteMaterialComponent.h"
#include "Texture.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(SpriteMaterialComponent, SPRITE_MATERIAL)

SpriteMaterialComponent::SpriteMaterialComponent(ABaseMaterial* material)
	: ABaseTextureMaterialComponent(material)
{
	this->addEditorProperty(new TextureEditorProperty{ "Sprite", &this->texture, ETextureMap::GUI });
}

} // namespace
