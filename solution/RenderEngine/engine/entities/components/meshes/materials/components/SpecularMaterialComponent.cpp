#include "SpecularMaterialComponent.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{
SpecularMaterialComponent::SpecularMaterialComponent(Material *material, const std::string &fileName)
	: NormalMaterialComponent(material, fileName)
{ }

void SpecularMaterialComponent::loadTexture(const std::string &fileName)
{
	Texture *newTexture = RenderManager::getInstance()->loadSpecularTexture(fileName);
	this->texture = UPTR<Texture>{ newTexture };
}

} // namespace
