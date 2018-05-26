#include "SpecularMaterialComponent.h"
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/graphics/RenderManager.h>

namespace sre
{
SpecularMaterialComponent::SpecularMaterialComponent(Material *material, const std::string &fileName)
	: NormalMaterialComponent(material, fileName)
{ }

void SpecularMaterialComponent::loadTexture(const std::string &fileName)
{
	Texture *newTexture = SingletonsManager::getInstance()->resolve<RenderManager>()->loadSpecularTexture(fileName);
	this->texture = UPTR<Texture>{ newTexture };
}

} // namespace
