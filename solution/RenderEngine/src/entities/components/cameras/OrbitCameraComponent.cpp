#include "OrbitCameraComponent.h"
#include "Input.h"
#include "TransformComponent.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"

#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

IMPLEMENT_CHILD_COMPONENT(OrbitCameraComponent, CameraComponent)

OrbitCameraComponent::OrbitCameraComponent(Entity* entity) : CameraComponent(entity){ }

void OrbitCameraComponent::onUpdate(float elapsedTime)
{
	processMouseMotion(elapsedTime);
}

void OrbitCameraComponent::processMouseMotion(float elapsedTime)
{
	const glm::ivec2& mouseDelta = Input::getMouseDeltaPosition();
	if ((mouseDelta.x != 0) || (mouseDelta.y != 0))
	{
		float deltaX = static_cast<float>(mouseDelta.x);
		float deltaY = static_cast<float>(mouseDelta.y);

		TransformComponent* transform = this->getTransform();

		const float SPEED = 1.5f;
		glm::vec3 position = transform->getPosition();
		glm::vec3 toPlayer = position - this->target;
		glm::vec3 direction = glm::normalize(toPlayer);
		glm::vec3 right = glm::cross(direction, glm::vec3{ 0.0f, 1.0f, 0.0f });
		glm::vec3 axis = glm::normalize((right * deltaY) + (glm::vec3{ 0.0f, 1.0f, 0.0f } *(-deltaX)));
		float angle = glm::vec2{ deltaX, deltaY }.length() * SPEED * elapsedTime;

		direction = glm::rotate(direction, angle, axis);

		float targetDistance = glm::length(toPlayer);
		position = this->target + (direction * targetDistance);

		transform->setPosition(position);
		transform->setLookAtRotation(this->target);
	}
}

} // namespace
