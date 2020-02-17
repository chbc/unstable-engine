#include "DirectionalLightComponent.h"

namespace sre
{

DirectionalLightComponent::DirectionalLightComponent(Entity *entity) : ALightComponent(entity)
{
}

void DirectionalLightComponent::setDirection(const glm::vec3 &direction)
{
	this->direction = direction;
}

glm::vec3 DirectionalLightComponent::getDirection()
{
    return this->direction;
}

} // namespace
