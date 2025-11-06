#include "EntityInputComponent.h"

#include "TransformComponent.h"
#include "Input.h"

#include <glm/vec2.hpp>

IMPLEMENT_COMPONENT(EntityInputComponent)

EntityInputComponent::EntityInputComponent(Entity* entity) : AEntityComponent(entity) {}

void EntityInputComponent::onUpdate(float elapsedTime)
{
	glm::vec3 direction = TransformComponent::ZERO;

	ControllerInput* controller = Input::getController(0);
	if (controller)
	{
		const glm::vec2& inputDirection = controller->getAnalogLeft();
		if ((inputDirection.x != 0.0f) || (inputDirection.y != 0.0f))
		{
			direction = glm::vec3{ inputDirection.x, 0.0f, -inputDirection.y };
		}

		if (controller->isButtonJustPressed(ControllerButton::BUTTON_A))
		{
			this->jumpSpeed = IMPULSE;
		}
	}

	this->jumpSpeed -= GRAVITY * elapsedTime;

	direction.y = this->jumpSpeed;

	glm::vec3 position = this->getTransform()->getPosition();
	position = position + (direction * elapsedTime * 5.0f);

	if (position.y < 0.5f)
	{
		position.y = 0.5;
		this->jumpSpeed = 0.0f;
	}

	this->getTransform()->setPosition(position);
}
