#include "ABaseTextureMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "TextureEditorProperty.h"

namespace sre
{
ABaseTextureMaterialComponent::ABaseTextureMaterialComponent(Material* material)
    : AMaterialComponent(material) {}

void ABaseTextureMaterialComponent::load(const char* fileName)
{
    TextureManager* textureManager = SingletonsManager::getInstance()->get<TextureManager>();
    this->texture = textureManager->loadTexture(fileName, getTextureType());
}

uint32_t ABaseTextureMaterialComponent::getTextureID() const
{
    return this->texture->getId();
}

} // namespace
