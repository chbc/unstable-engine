#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"

namespace sre
{

IMPLEMENT_COMPONENT(BoxColliderComponent)

BoxColliderComponent::BoxColliderComponent(Entity* entity) : AEntityComponent(entity)
{
	entity->getBounds(this->bounds);
}

bool BoxColliderComponent::intersects(BoxColliderComponent* other)
{
	const glm::vec3& position = this->getTransform()->getPosition();
	const glm::vec3& otherPosition = other->getTransform()->getPosition();

	return this->bounds.intersects(position, otherPosition, other->bounds);
}

} // namespace
