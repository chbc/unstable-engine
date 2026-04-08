#include "SkyboxComponent.h"
#include "ABaseMaterial.h"
#include "SingletonsManager.h"
#include "RenderManager.h"

namespace sre
{
IMPLEMENT_CHILD_COMPONENT(SkyboxComponent, MeshComponent)

SkyboxComponent::SkyboxComponent(Entity* entity) : MeshComponent(entity)
{ }

void SkyboxComponent::onPropertyChanged()
{
	ARenderableComponent::onPropertyChanged();
	RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
	renderManager->reloadSkyboxMaterial(this->getMaterial());
}

} // namespace
