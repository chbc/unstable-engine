#include "ABaseTextureMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "TextureEditorProperty.h"

namespace sre
{
ABaseTextureMaterialComponent::ABaseTextureMaterialComponent(Material* material)
    : AMaterialComponent(material) {}

uint32_t ABaseTextureMaterialComponent::getTextureID() const
{
    return this->texture->getId();
}

} // namespace
