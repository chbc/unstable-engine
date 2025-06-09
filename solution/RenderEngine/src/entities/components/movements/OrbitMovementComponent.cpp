#include "OrbitMovementComponent.h"
#include "TransformComponent.h"

#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(OrbitMovementComponent)

OrbitMovementComponent::OrbitMovementComponent(Entity* entity) : AEntityComponent(entity){ }

void OrbitMovementComponent::move(const glm::vec2& deltaMovement, float elapsedTime)
{
	if ((deltaMovement.x != 0.0f) || (deltaMovement.y != 0.0f))
	{
		float deltaX = deltaMovement.x;
		float deltaY = deltaMovement.y;

		TransformComponent* transform = this->getTransform();

		const float SPEED = 10.0f;
		glm::vec3 position = transform->getPosition();
		glm::vec3 toPlayer = position - this->target;
		glm::vec3 direction = glm::normalize(toPlayer);
		glm::vec3 right = glm::cross(direction, glm::vec3{ 0.0f, 1.0f, 0.0f });
		glm::vec3 axis = glm::normalize((right * deltaY) + (glm::vec3{ 0.0f, 1.0f, 0.0f } *(-deltaX)));
		float angle = (glm::abs(deltaX) + glm::abs(deltaY)) * SPEED * elapsedTime;

		direction = glm::rotate(direction, glm::radians(angle), axis);

		float targetDistance = glm::length(toPlayer);
		position = this->target + (direction * targetDistance);

		transform->setPosition(position);
		transform->setLookAtRotation(this->target);
	}
}

} // namespace
