#include "ALightComponent.h"
#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/entities/Entity.h>

namespace sre
{

ALightComponent::ALightComponent(Entity *entity) : AEntityComponent(entity)
{
    this->color = glm::vec3(0.6f, 0.6f, 0.6f);
}

void ALightComponent::setColor(const glm::vec3 &color)
{
    this->color = color;
}

glm::vec3 ALightComponent::getColor()
{
	return this->color;
}

} // namespace
