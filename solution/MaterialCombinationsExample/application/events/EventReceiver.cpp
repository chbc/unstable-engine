#include "EventReceiver.h"
#include "application/SampleApplication.h"
#include <Input.h>

#include <glm/vec3.hpp>

EventReceiver::EventReceiver(SampleApplication *application, CameraComponent *camera)
{
	this->application = application;
	this->camera = camera;

	glm::vec3 position(0.0f, 2.5f, 10.0f);
	this->camera->setPosition(position);
}

void EventReceiver::processInput()
{
	this->processKeys();
	this->processMouse();
}

void EventReceiver::processKeys()
{
	if (Input::isKeyDown(KEY_ESC))
		this->application->quit();
	else if (Input::isKeyDown(KEY_e))
		this->application->setEditorMode(true);
}

void EventReceiver::processMouse()
{
	if (Input::isMouseButtonDown(MOUSEBUTTON_LEFT))
	{
		glm::vec3 position = this->camera->getPosition();
		position.x -= 1.0f;
		this->camera->setPosition(position);
	}
	else if (Input::isMouseButtonDown(MOUSEBUTTON_RIGHT))
	{
		glm::vec3 position = this->camera->getPosition();
		position.x += 1.0f;
		this->camera->setPosition(position);
	}
}
