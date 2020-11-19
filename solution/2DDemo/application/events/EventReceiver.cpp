#include "EventReceiver.h"
#include "application/SampleApplication.h"
#include <glm/glm.hpp>

EventReceiver::EventReceiver(SampleApplication *application, CameraComponent *camera)
{
	this->application = application;
	this->camera = camera;

	glm::vec3 position(0.0f, 0.0f, 5.0f);
	this->camera->setPosition(position);
	this->cameraDistance = glm::distance(position, glm::vec3(0, 0, 0));

	this->viewingActive = false;
}

void EventReceiver::onQuit()
{
	this->application->quit();
}

void EventReceiver::onKeyPressed(KeyboardButton key)
{
	if (key == KEY_ESC)
		this->application->quit();

	/*
	else if (key == KEY_1)
	{
		this->effectValue -= 0.025f;
		this->ppEffect->setValue("exposure", this->effectValue);
		std::cout << "EXPOSURE = " << this->effectValue << std::endl;
	}
	else if (key == KEY_2)
	{
		this->effectValue += 0.025f;
		this->ppEffect->setValue("exposure", this->effectValue);
		std::cout << "EXPOSURE = " << this->effectValue << std::endl;
	}
	else if (key == KEY_0)
	{
		int value = this->ppEffect->getValue("enabled");
		value = (value > 0) ? 0 : 1;
		this->ppEffect->setValue("enabled", value);

		if (value > 0)
			std::cout << "HDR ON";
		else
			std::cout << "HDR OFF";
	}
	*/
}

void EventReceiver::onMouseButtonPressed(MouseButton mouseButton, const glm::vec2 &position)
{
	static float yLookAt = 0.0f;

	this->viewingActive = true;
	if (mouseButton == MOUSEBUTTON_MIDDLE)
	{
		yLookAt += 1.0f;
		this->camera->setLookAt(glm::vec3(0.0f, yLookAt, 0.0f));
	}
}

void EventReceiver::onMouseButtonReleased(MouseButton mouseButton, const glm::vec2 &position)
{
	this->viewingActive = false;
}

void EventReceiver::onMouseMoveRelative(const glm::vec2 &relativePosition)
{
	if (this->viewingActive)
	{
		const float SPEED = 0.02f;
		glm::vec3 position = this->camera->getTransform()->getPosition();
		position.x += relativePosition.x * SPEED;
		position.y -= relativePosition.y * SPEED;
		this->camera->setPosition(position);
		this->camera->setLookAt(glm::vec3(position.x, position.y, 0.0f));
	}
}

void EventReceiver::onMouseWheel(int direction)
{
	this->cameraDistance -= direction;
	
	glm::vec3 position = this->camera->getTransform()->getPosition();
	position = glm::normalize(position);
	position *= this->cameraDistance;

	this->camera->setPosition(position);
}
