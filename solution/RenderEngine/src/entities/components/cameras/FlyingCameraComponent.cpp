#include "FlyingCameraComponent.h"
#include "TransformComponent.h"
#include "Input.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"

#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

IMPLEMENT_CHILD_COMPONENT(FlyingCameraComponent, CameraComponent)

FlyingCameraComponent::FlyingCameraComponent(Entity* entity) : CameraComponent(entity){}

void FlyingCameraComponent::onUpdate(float elapsedTime)
{
	if (Input::isMouseButtonDown(MouseButton::MOUSEBUTTON_RIGHT))
	{
		this->processKeys();
		this->processMouseMotion(elapsedTime);
		this->processMouseWheel(elapsedTime);
		this->updateMovement(elapsedTime);
	}
}

void FlyingCameraComponent::processKeys()
{
	TransformComponent* transform = this->getTransform();
	
	this->moveDirection.x = 0.0f;
	this->moveDirection.y = 0.0f;
	this->moveDirection.z = 0.0f;

	if (Input::isKeyDown(KEY_a))
		this->moveDirection -= transform->getRight();
	if (Input::isKeyDown(KEY_d))
		this->moveDirection += transform->getRight();
	if (Input::isKeyDown(KEY_w))
		this->moveDirection -= transform->getForward();
	if (Input::isKeyDown(KEY_s))
		this->moveDirection += transform->getForward();
}

void FlyingCameraComponent::processMouseMotion(float elapsedTime)
{
	static float pitch = 0.0f;
	static float yaw = 0.0f;

	const glm::ivec2& mouseDelta = Input::getMouseDeltaPosition();
	if ((mouseDelta.x != 0) || (mouseDelta.y != 0))
	{
		const float SPEED = 15.0f;
		float deltaX = static_cast<float>(mouseDelta.x);
		float deltaY = static_cast<float>(mouseDelta.y);

		this->yaw -= deltaX * SPEED * elapsedTime;
		this->pitch -= deltaY * SPEED * elapsedTime;

		this->pitch = glm::clamp(this->pitch, -89.0f, 89.0f);

		this->getTransform()->setRotation(TransformComponent::UP, this->yaw);
		this->getTransform()->rotate(TransformComponent::RIGHT, this->pitch);
	}
}

void FlyingCameraComponent::processMouseWheel(float elapsedTime)
{
	int mouseWheel = Input::getMouseWheel();
	if (mouseWheel != 0)
	{
		const float WHEEL_RATE = 100.0f;
		this->moveSpeed += static_cast<float>(mouseWheel) * WHEEL_RATE * elapsedTime;
		this->moveSpeed = glm::clamp(this->moveSpeed, 0.1f, 100.0f);
	}
}

void FlyingCameraComponent::updateMovement(float elapsedTime)
{
	if ((this->moveDirection.x != 0.0f) || (this->moveDirection.y != 0.0f) || (this->moveDirection.z != 0.0f))
	{
		TransformComponent* transform = this->getTransform();
		glm::vec3 position = transform->getPosition();

		glm::vec3 step = glm::normalize(this->moveDirection) * (moveSpeed * elapsedTime);
		position += step;

		transform->setPosition(position);
	}
}

} // namespace
