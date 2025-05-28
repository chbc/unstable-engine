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
	static float pitch = 0.0f;
	static float yaw = 0.0f;

	if ((mouseDelta.x != 0.0f) || (mouseDelta.y != 0.0f))
	{
		const float SPEED = 15.0f;
		float deltaX = mouseDelta.x;
		float deltaY = mouseDelta.y;

		this->yaw -= deltaX * SPEED * elapsedTime;
		this->pitch -= deltaY * SPEED * elapsedTime;

		this->pitch = glm::clamp(this->pitch, -89.0f, 89.0f);

		this->getTransform()->setRotation(TransformComponent::UP, this->yaw);
		this->getTransform()->rotate(TransformComponent::RIGHT, this->pitch);
	}
}

void FlyingMovementComponent::addSpeed(float mouseWheel, float elapsedTime)
{
	const float WHEEL_RATE = 50.0f;
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
