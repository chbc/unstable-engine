#include "PanMovementComponent.h"
#include "TransformComponent.h"

namespace sre
{

IMPLEMENT_COMPONENT(PanMovementComponent)

PanMovementComponent::PanMovementComponent(Entity* entity) : AEntityComponent(entity) {}

void PanMovementComponent::move(const glm::vec2& deltaMovement, float elapsedTime)
{
	if ((deltaMovement.x != 0.0f) || (deltaMovement.y != 0.0f))
	{
		float deltaX = deltaMovement.x;
		float deltaY = deltaMovement.y;
		TransformComponent* transform = this->getTransform();
		const float SPEED = 1.0f;
		glm::vec3 position = transform->getPosition();
		glm::vec3 right = transform->getRight();
		glm::vec3 up = transform->getUp();
		position += (right * (-deltaX) + up * (deltaY)) * SPEED * elapsedTime;
		transform->setPosition(position);
	}
}

} // namespace
