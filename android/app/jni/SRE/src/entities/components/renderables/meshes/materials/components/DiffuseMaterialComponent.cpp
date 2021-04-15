#include "DiffuseMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"

namespace sre
{

DiffuseMaterialComponent::DiffuseMaterialComponent(Material *material, const std::string &fileName) 
    : AMaterialComponent(material)
{
    this->texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadTexture(fileName, EMaterialMap::DIFFUSE);
}

uint32_t DiffuseMaterialComponent::getTextureID(uint32_t index) const
{
    return this->texture->getId();
}

} // namespace
