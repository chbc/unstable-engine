#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include <engine/systems/input/InputHandler.h>
#include <engine/entities/components/cameras/CameraComponent.h>

using namespace sre;

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

		void onQuit() override;
		void onKeyPressed(KeyboardButton key) override;
		void onMouseButtonPressed(MouseButton mouseButton, const glm::vec2 &position) override;
		void onMouseButtonReleased(MouseButton mouseButton, const glm::vec2 &position) override;
		void onMouseMove(const glm::vec2 &relativePosition) override;
		void onMouseWheelMove(int direction) override;
};

#endif
