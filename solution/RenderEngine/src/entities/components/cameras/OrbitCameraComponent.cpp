#include "OrbitCameraComponent.h"
#include "Input.h"
#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(OrbitCameraComponent)

OrbitCameraComponent::OrbitCameraComponent(Entity* entity) : CameraComponent(entity), targetDistance(0.0f) { }

void OrbitCameraComponent::onStart()
{
	const glm::vec3 position = this->getPosition();
	this->targetDistance = glm::distance(position, this->lookAtTarget);
}

void OrbitCameraComponent::onUpdate(uint32_t elapsedTime)
{
	processMouseWheel();
	processMouseMotion();
}

void OrbitCameraComponent::processMouseWheel()
{
	int mouseWheel = Input::getMouseWheel();

	if (mouseWheel != 0)
	{
		this->targetDistance -= mouseWheel;
		this->targetDistance = (this->targetDistance < 0.0f) ? 0.0f : this->targetDistance;

		glm::vec3 position = this->getPosition();
		position = glm::normalize(position);
		position *= this->targetDistance;

		this->setPosition(position);
	}
}

void OrbitCameraComponent::processMouseMotion()
{
	const glm::ivec2& mouseDelta = Input::getMouseDeltaPosition();
	if ((mouseDelta.x != 0) || (mouseDelta.y != 0))
	{
		float deltaX = static_cast<float>(mouseDelta.x);
		float deltaY = static_cast<float>(mouseDelta.y);

		const float SPEED = 0.02f;
		glm::vec3 position = this->getPosition();

		glm::vec3 direction = glm::normalize(position - this->lookAtTarget);
		glm::vec3 right = glm::cross(direction, glm::vec3{ 0.0f, 1.0f, 0.0f });
		glm::vec3 axis = glm::normalize((right * deltaY) + (glm::vec3{ 0.0f, 1.0f, 0.0f } *(-deltaX)));
		float angle = glm::vec2{ deltaX, deltaY }.length() * SPEED;

		direction = glm::rotate(direction, angle, axis);
		position = direction * this->targetDistance;

		this->setPosition(position);
	}
}

} // namespace
