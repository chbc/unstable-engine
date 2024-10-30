#include "SpriteMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(SpriteMaterialComponent)

SpriteMaterialComponent::SpriteMaterialComponent(Material* material, const std::string& fileName)
	: AMaterialComponent(material)
{
	this->texture = SingletonsManager::getInstance()->get<TextureManager>()->loadTexture(fileName, EMaterialMap::GUI);
	this->addEditorProperty(new TextureEditorProperty{ "Sprite", this->texture->getId() });
}

uint32_t SpriteMaterialComponent::getTextureID() const
{
	return this->texture->getId();
}

} // namespace
