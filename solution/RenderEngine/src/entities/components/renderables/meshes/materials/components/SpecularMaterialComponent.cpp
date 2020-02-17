#include "SpecularMaterialComponent.h"
#include "SingletonsManager.h"
#include "RenderManager.h"

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
