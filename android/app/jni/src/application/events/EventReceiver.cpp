#include "EventReceiver.h"
#include "application/SampleApplication.h"
#include <Entity.h>
#include <glm/glm.hpp>
#include "EngineValues.h"

EventReceiver::EventReceiver(SampleApplication *arg_application, Entity* arg_entity)
	: application(arg_application), entity(arg_entity)
{
	this->isScreenPressed = false;
}

void EventReceiver::onQuit()
{
	this->application->quit();
}

void EventReceiver::onMouseButtonEvent(MouseButton mouseButton, const glm::vec2& position, bool pressed)
{
	glm::vec3 newPosition = this->entity->getTransform()->getPosition();
	newPosition.x = position.x - (EngineValues::SCREEN_WIDTH * 0.5f);
	newPosition.y = (position.y + (EngineValues::SCREEN_HEIGHT * 0.5f)) - (position.y * 2.0f);

	this->entity->getTransform()->setPosition(newPosition);

	this->isScreenPressed = pressed;
}

void EventReceiver::onMouseMove(const glm::vec2& position)
{
	if (this->isScreenPressed)
	{
		glm::vec3 newPosition = this->entity->getTransform()->getPosition();
		newPosition.x = position.x - (EngineValues::SCREEN_WIDTH * 0.5f);
		newPosition.y = (position.y + (EngineValues::SCREEN_HEIGHT * 0.5f)) - (position.y * 2.0f);

		this->entity->getTransform()->setPosition(newPosition);
	}
}
