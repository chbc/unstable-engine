#include "FlyingMovementComponent.h"
#include "TransformComponent.h"

#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(FlyingMovementComponent)

FlyingMovementComponent::FlyingMovementComponent(Entity* entity) : AEntityComponent(entity) { }

void FlyingMovementComponent::processMovement(const glm::vec3& moveDirection, const glm::vec2& mouseDelta, float elapsedTime)
{
	this->updateOrientation(mouseDelta, elapsedTime);
	this->updateMovement(moveDirection, elapsedTime);
}

void FlyingMovementComponent::updateOrientation(const glm::vec2& mouseDelta, float elapsedTime)
{
	if ((mouseDelta.x != 0.0f) || (mouseDelta.y != 0.0f))
	{
		const float SPEED = 15.0f;
		float deltaX = -mouseDelta.x;
		float deltaY = mouseDelta.y;

		TransformComponent* transform = this->getTransform();
		float pitch, yaw, roll;
		transform->getRotation(pitch, yaw, roll);

		yaw += deltaX * SPEED * elapsedTime;
		pitch += deltaY * SPEED * elapsedTime;
		pitch = glm::clamp(pitch, -89.0f, 89.0f);

		transform->setRotation(TransformComponent::UP, yaw);
		transform->rotate(TransformComponent::RIGHT, pitch);
	}
}

void FlyingMovementComponent::addSpeed(float mouseWheel, float elapsedTime)
{
	this->moveSpeed += mouseWheel * WHEEL_RATE * elapsedTime;
	this->moveSpeed = glm::clamp(this->moveSpeed, 0.1f, 100.0f);
}

void FlyingMovementComponent::updateMovement(const glm::vec3& moveDirection, float elapsedTime)
{
	if ((moveDirection.x != 0.0f) || (moveDirection.y != 0.0f) || (moveDirection.z != 0.0f))
	{
		TransformComponent* transform = this->getTransform();
		glm::vec3 position = transform->getPosition();

		glm::vec3 step = glm::normalize(moveDirection) * (moveSpeed * elapsedTime);
		position += step;

		transform->setPosition(position);
	}
}

} // namespace
