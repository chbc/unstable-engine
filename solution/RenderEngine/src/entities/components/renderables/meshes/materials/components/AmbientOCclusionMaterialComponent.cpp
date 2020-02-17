#include "AmbientOcclusionMaterialComponent.h"
#include "SingletonsManager.h"
#include "RenderManager.h"

namespace sre
{
AmbientOcclusionMaterialComponent::AmbientOcclusionMaterialComponent(Material *material, const std::string &fileName)
	: NormalMaterialComponent(material, fileName)
{ }

void AmbientOcclusionMaterialComponent::loadTexture(const std::string &fileName)
{
	Texture *newTexture = SingletonsManager::getInstance()->resolve<RenderManager>()->loadAOTexture(fileName);
	this->texture = UPTR<Texture>{ newTexture };
}

} // namespace
