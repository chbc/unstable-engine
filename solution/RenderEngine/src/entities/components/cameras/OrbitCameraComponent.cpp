#include "OrbitCameraComponent.h"
#include "Input.h"
#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <stdio.h>

namespace sre
{

IMPLEMENT_COMPONENT(OrbitCameraComponent)

OrbitCameraComponent::OrbitCameraComponent(Entity* entity) : CameraComponent(entity){ }

void OrbitCameraComponent::onStart()
{
}

void OrbitCameraComponent::onUpdate(uint32_t elapsedTime)
{
	processMouseMotion(elapsedTime);
}

void OrbitCameraComponent::processMouseMotion(uint32_t elapsedTime)
{
	const glm::ivec2& mouseDelta = Input::getMouseDeltaPosition();
	if ((mouseDelta.x != 0) || (mouseDelta.y != 0))
	{
		float deltaX = static_cast<float>(mouseDelta.x);
		float deltaY = static_cast<float>(mouseDelta.y);

		const float SPEED = 0.001f;
		glm::vec3 position = this->getPosition();
		glm::vec3 toPlayer = position - this->lookAtTarget;
		glm::vec3 direction = glm::normalize(toPlayer);
		glm::vec3 right = glm::cross(direction, glm::vec3{ 0.0f, 1.0f, 0.0f });
		glm::vec3 axis = glm::normalize((right * deltaY) + (glm::vec3{ 0.0f, 1.0f, 0.0f } *(-deltaX)));
		float angle = glm::vec2{ deltaX, deltaY }.length() * SPEED * elapsedTime;

		direction = glm::rotate(direction, angle, axis);

		float targetDistance = glm::length(toPlayer);
		position = this->lookAtTarget + (direction * targetDistance);

		this->setPosition(position);
	}
}

} // namespace