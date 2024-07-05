#include "FlyingCameraComponent.h"
#include "TransformComponent.h"
#include "Input.h"
#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(FlyingCameraComponent)

FlyingCameraComponent::FlyingCameraComponent(Entity* entity) : CameraComponent(entity){}

void FlyingCameraComponent::onUpdate(float elapsedTime)
{
	if (Input::isMouseButtonDown(MouseButton::MOUSEBUTTON_RIGHT))
	{
		processKeys();
		processMouseMotion(elapsedTime);
		updateMovement(elapsedTime);
	}

	this->lastMousePosition = Input::getMousePosition();
}

void FlyingCameraComponent::processKeys()
{
	glm::vec3 position = this->getPosition();
	glm::vec3 forward = glm::normalize(this->lookAtTarget - position);
	glm::vec3 right = glm::cross(forward, glm::vec3{ 0.0f, 1.0f, 0.0f });
	
	this->moveDirection.x = 0.0f;
	this->moveDirection.y = 0.0f;
	this->moveDirection.z = 0.0f;

	if (Input::isKeyDown(KEY_a))
		this->moveDirection -= right;
	if (Input::isKeyDown(KEY_d))
		this->moveDirection += right;
	if (Input::isKeyDown(KEY_w))
		this->moveDirection += forward;
	if (Input::isKeyDown(KEY_s))
		this->moveDirection -= forward;
}

void FlyingCameraComponent::processMouseMotion(float elapsedTime)
{
	const glm::ivec2& mousePosition = Input::getMousePosition();
	const glm::ivec2& mouseDelta = mousePosition - this->lastMousePosition;
	if ((mouseDelta.x != 0) || (mouseDelta.y != 0))
	{
		float deltaX = static_cast<float>(mouseDelta.x);
		float deltaY = static_cast<float>(-mouseDelta.y);

		const float SPEED = 2.0f;
		glm::vec3 position = this->getPosition();

		this->rotateDirection = glm::normalize(this->lookAtTarget - position);
		glm::vec3 right = glm::cross(this->rotateDirection, glm::vec3{ 0.0f, 1.0f, 0.0f });
		glm::vec3 axis = glm::normalize((right * deltaY) + (glm::vec3{ 0.0f, 1.0f, 0.0f } *(-deltaX)));
		float angle = glm::vec2{ deltaX, deltaY }.length() * SPEED * elapsedTime;

		this->rotateDirection = glm::rotate(this->rotateDirection, angle, axis);
		float targetDistance = glm::distance(position, this->lookAtTarget);
		this->lookAtTarget = position + (this->rotateDirection * targetDistance);
	}
}

void FlyingCameraComponent::updateMovement(float elapsedTime)
{
	if ((this->moveDirection.x != 0.0f) || (this->moveDirection.y != 0.0f) || (this->moveDirection.z != 0.0f))
	{
		const float SPEED = 10.0f;
		glm::vec3 position = this->getPosition();

		glm::vec3 step = glm::normalize(this->moveDirection) * (SPEED * elapsedTime);
		this->lookAtTarget += step;
		position += step;

		this->setPosition(position);
	}
}

} // namespace
