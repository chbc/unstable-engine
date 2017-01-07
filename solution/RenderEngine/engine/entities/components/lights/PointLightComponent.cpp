#include "PointLightComponent.h"
#include <engine/entities/components/transforms/TransformComponent.h>

namespace sre
{

void PointLightComponent::setPosition(const glm::vec3 &position)
{
	this->getTransform()->setPosition(position);
}

glm::vec3 PointLightComponent::getPosition()
{
	return this->getTransform()->getPosition();
}

PointLightComponent::PointLightComponent(Entity *entity) : ALightComponent(entity)
{
}

} // namespace
