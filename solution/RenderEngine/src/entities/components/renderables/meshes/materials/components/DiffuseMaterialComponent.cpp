#include "DiffuseMaterialComponent.h"
#include <iostream>
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "Texture.h"

namespace sre
{

DiffuseMaterialComponent::DiffuseMaterialComponent(Material *material, const std::string &fileName) 
    : AMaterialComponent(material)
{
    this->loadTexture(fileName);
}

void DiffuseMaterialComponent::loadTexture(const std::string &fileName)
{
    this->texture = SingletonsManager::getInstance()->resolve<RenderManager>()->loadDiffuseTexture(fileName);
}

uint32_t DiffuseMaterialComponent::getTextureID(uint32_t index)
{
    return this->texture->getId();
}

} // namespace
