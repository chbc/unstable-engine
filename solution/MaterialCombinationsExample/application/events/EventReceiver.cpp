#include "EventReceiver.h"
#include "application/SampleApplication.h"
#include <glm/glm.hpp>

#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

EventReceiver::EventReceiver(SampleApplication *application, CameraComponent *camera)
{
	this->application = application;
	this->camera = camera;

	glm::vec3 position(0.0f, 2.5f, 10.0f);
	this->camera->setPosition(position);
}

void EventReceiver::onQuit()
{
	this->application->quit();
}

void EventReceiver::onKeyEvent(KeyboardButton key, bool pressed)
{
	if (pressed)
	{
		if (key == KEY_ESC)
			this->application->quit();
		else if (key == KEY_e)
			this->application->setEditorMode(true);
	}
}

void EventReceiver::onMouseButtonEvent(MouseButton mouseButton, const glm::vec2 &position, bool pressed)
{
	if (pressed)
	{
		glm::vec3 position = this->camera->getPosition();
		if (mouseButton == MOUSEBUTTON_LEFT)
			position.x -= 1.0f;
		else
			position.x += 1.0f;

		this->camera->setPosition(position);
	}
}
