#include "DirectionalLightComponent.h"
#include "SingletonsManager.h"
#include "LightManager.h"

namespace sre
{

IMPLEMENT_COMPONENT(DirectionalLightComponent)

DirectionalLightComponent::DirectionalLightComponent(Entity *entity) : ALightComponent(entity)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	LightManager* lightManager = singletonsManager->get<LightManager>();
	lightManager->addDirectionalLight(this);
}

} // namespace
