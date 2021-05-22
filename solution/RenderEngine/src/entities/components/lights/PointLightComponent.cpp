#include "PointLightComponent.h"
#include "TransformComponent.h"
#include "FloatEditorProperty.h"

namespace sre
{

IMPLEMENT_COMPONENT(PointLightComponent)

PointLightComponent::PointLightComponent(Entity *entity) 
    : ALightComponent(entity), range(20.0f), intensity(2.0f)
{
	this->addEditorProperty(new FloatEditorProperty{ "Intensity", &this->intensity });
	this->addEditorProperty(new FloatEditorProperty{ "Range", &this->range });
}

void PointLightComponent::setPosition(const glm::vec3 &position)
{
	this->getTransform()->setPosition(position);
}

glm::vec3 PointLightComponent::getPosition()
{
	return this->getTransform()->getPosition();
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
