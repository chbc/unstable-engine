#include "DiffuseMaterialComponent.h"
#include <iostream>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/graphics/RenderManager.h>
#include <engine/core/multimedia/textures/Texture.h>

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
