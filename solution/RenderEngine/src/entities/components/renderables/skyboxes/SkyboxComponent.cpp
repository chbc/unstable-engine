#include "SkyboxComponent.h"
#include "ABaseMaterial.h"
#include "SingletonsManager.h"
#include "RenderManager.h"

namespace sre
{
IMPLEMENT_COMPONENT(SkyboxComponent)

SkyboxComponent::SkyboxComponent(Entity* entity) : MeshComponent(entity)
{ }

void SkyboxComponent::onPropertyChanged()
{
	ARenderableComponent::onPropertyChanged();
	RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
	renderManager->reloadSkyboxMaterial(this->getMaterial());
}

} // namespace
