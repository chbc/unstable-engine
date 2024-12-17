#include "DiffuseMaterialComponent.h"
#include "TextureEditorProperty.h"
#include "Texture.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(DiffuseMaterialComponent, DIFFUSE_MATERIAL)

DiffuseMaterialComponent::DiffuseMaterialComponent(Material *material)
    : ABaseTextureMaterialComponent(material)
{
    this->addEditorProperty(new TextureEditorProperty{ "Diffuse", &this->texture->getId() });
}

ETextureMap::Type DiffuseMaterialComponent::getTextureType()
{
    return ETextureMap::DIFFUSE;
}

} // namespace
