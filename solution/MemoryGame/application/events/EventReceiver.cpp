#include "EventReceiver.h"
#include "application/SampleApplication.h"
#include <Entity.h>
#include <glm/glm.hpp>
#include <SDL_log.h>

EventReceiver::EventReceiver(SampleApplication *arg_application, Entity* arg_entity)
	: application(arg_application), entity(arg_entity)
{

}

void EventReceiver::onQuit()
{
	this->application->quit();
}

void EventReceiver::onMouseButtonPressed(MouseButton mouseButton, const glm::vec2 &position)
{
	glm::vec3 newPosition = this->entity->getTransform()->getPosition();
	newPosition.x = (position.x) - (800 * 0.5);
	newPosition.y = (1247.0f - (position.y * 2.0)) * 0.5f;

	this->entity->getTransform()->setPosition(newPosition);

	SDL_Log("XXX POSICAO (%.2f, %.2f)", position.x, position.y);
	SDL_Log("XXX newPosition (%.2f, %.2f)", newPosition.x, newPosition.y);
}

void EventReceiver::onMouseMoveRelative(const glm::vec2 &relativePosition)
{
	glm::vec3 newPosition = this->entity->getTransform()->getPosition();
	newPosition.x += relativePosition.x;
	newPosition.y -= relativePosition.y;
	
	this->entity->getTransform()->setPosition(newPosition);
}
