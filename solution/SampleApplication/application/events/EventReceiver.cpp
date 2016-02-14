#include "EventReceiver.h"
#include <application/SampleApplication.h>

EventReceiver::EventReceiver(SampleApplication *application, CameraNode *camera)
{
	this->application = application;
	this->camera = camera;

	Vector position(0, 0, 5);
	this->camera->setPosition(position);
	this->cameraDistance = position.distance(Vector(0, 0, 0));

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
}

void EventReceiver::onMouseButtonPressed(MouseButton button, Vector position)
{
	this->viewingActive = true;
}

void EventReceiver::onMouseButtonReleased(MouseButton button, Vector position)
{
	this->viewingActive = false;
}

void EventReceiver::onMouseMove(Vector relativePosition)
{
	if (this->viewingActive)
	{
		const float SPEED = 0.5f;
		Vector position = this->camera->getTransform()->getPosition();

		Vector direction = (position - Vector::ZERO).normalize();
		Vector right = direction.cross(Vector::UP);
		Vector axis = ((right * relativePosition.y) + (Vector(0, 1, 0) * (-relativePosition.x))).normalize();

		direction = direction.rotate(axis, relativePosition.magnitude() * SPEED);
		
		position = direction * this->cameraDistance;
		
		this->camera->setPosition(position);

	}
}
