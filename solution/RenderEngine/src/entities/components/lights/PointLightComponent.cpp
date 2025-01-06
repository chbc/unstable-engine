#include "PointLightComponent.h"
#include "TransformComponent.h"
#include "FloatEditorProperty.h"
#include "SingletonsManager.h"
#include "LightManager.h"

namespace sre
{

IMPLEMENT_COMPONENT(PointLightComponent)

PointLightComponent::PointLightComponent(Entity *entity) 
    : ALightComponent(entity), range(20.0f), intensity(2.0f)
{
	this->addEditorProperty(new FloatEditorProperty{ "Intensity", &this->intensity });
	this->addEditorProperty(new FloatEditorProperty{ "Range", &this->range });

	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	LightManager* lightManager = singletonsManager->get<LightManager>();
	lightManager->addPointLight(this);
}

void PointLightComponent::setRange(float range)
{
	this->range = range;
}

float PointLightComponent::getRange()
{
	return this->range;
}

void PointLightComponent::setIntensity(float intensity)
{
	this->intensity = intensity;
}

float PointLightComponent::getIntensity()
{
	return this->intensity;
}

} // namespace
