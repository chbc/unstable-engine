#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include <engine/systems/input/InputHandler.h>
#include <engine/entities/components/cameras/CameraComponent.h>

using namespace sre;

// forward Game declaration
class SampleApplication;

/*!
	Class that turns input events into application events
*/
class EventReceiver : public InputHandler
{
	private:
		SampleApplication *application;
		CameraComponent *camera;

		float cameraDistance;

		bool viewingActive;

	public:
		EventReceiver(SampleApplication *application, CameraComponent *camera);

		void onQuit();
		void onKeyPressed(KeyboardButton key);
		void onMouseButtonPressed(MouseButton mouseButton, const glm::vec2 &position);
		void onMouseButtonReleased(MouseButton mouseButton, const glm::vec2 &position);
		void onMouseMove(const glm::vec2 &relativePosition);
};

#endif
