#include "NormalMaterialComponent.h"
#include "Texture.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(NormalMaterialComponent, NORMAL_MATERIAL)

NormalMaterialComponent::NormalMaterialComponent(Material *material)
	: ABaseTextureMaterialComponent(material)
{
	this->addEditorProperty(new TextureEditorProperty{ "Normal", &this->texture, ETextureMap::NORMAL });
}

} // namespace
