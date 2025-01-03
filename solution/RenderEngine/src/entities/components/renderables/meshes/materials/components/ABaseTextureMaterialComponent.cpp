#include "ABaseTextureMaterialComponent.h"
#include "Texture.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"

namespace sre
{
ABaseTextureMaterialComponent::ABaseTextureMaterialComponent(Material* material)
    : AMaterialComponent(material), texture(nullptr) {}

ABaseTextureMaterialComponent::~ABaseTextureMaterialComponent()
{
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	assetsManager->releaseTexture(this->texture);
}

uint32_t ABaseTextureMaterialComponent::getTextureID() const
{
    return this->texture->getId();
}

} // namespace
