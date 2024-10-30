#include "DiffuseMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(DiffuseMaterialComponent)

DiffuseMaterialComponent::DiffuseMaterialComponent(Material *material, const std::string &fileName) 
    : AMaterialComponent(material)
{
    this->texture = SingletonsManager::getInstance()->get<TextureManager>()->loadTexture(fileName, EMaterialMap::DIFFUSE);
    this->addEditorProperty(new TextureEditorProperty{ "Diffuse", this->texture->getId() });
}

uint32_t DiffuseMaterialComponent::getTextureID(uint32_t index) const
{
    return this->texture->getId();
}

} // namespace
