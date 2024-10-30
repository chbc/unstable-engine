#include "NormalMaterialComponent.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "TextureEditorProperty.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(NormalMaterialComponent)

NormalMaterialComponent::NormalMaterialComponent(Material *material, const std::string &fileName)
	: AMaterialComponent(material)
{
	this->texture = SingletonsManager::getInstance()->get<TextureManager>()->loadTexture(fileName, EMaterialMap::NORMAL);
	this->addEditorProperty(new TextureEditorProperty{ "Normal", this->texture->getId() });
}

uint32_t NormalMaterialComponent::getTextureID() const
{
	return this->texture->getId();
}

} // namespace
