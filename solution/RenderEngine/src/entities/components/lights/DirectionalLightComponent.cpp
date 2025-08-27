#include "DirectionalLightComponent.h"
#include "TransformComponent.h"
#include "SingletonsManager.h"
#include "LightManager.h"

namespace sre
{

IMPLEMENT_COMPONENT(DirectionalLightComponent)

DirectionalLightComponent::DirectionalLightComponent(Entity *entity) : ALightComponent(entity)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->lightManager = singletonsManager->get<LightManager>();
	this->lightManager->addDirectionalLight(this);

	TransformComponent* transform = this->getTransform();
	transform->addPropertyChangedCallback([this]() { this->lightManager->updateDirectionalLightsUBO(); });
}

void DirectionalLightComponent::onPropertyChanged()
{
	AEntityComponent::onPropertyChanged();
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	LightManager* lightManager = singletonsManager->get<LightManager>();
	lightManager->updateDirectionalLightsUBO();
}

} // namespace
