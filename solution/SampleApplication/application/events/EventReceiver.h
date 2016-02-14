#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include <engine/systems/input/InputHandler.h>
#include <engine/nodes/CameraNode.h>

using namespace input;
using nodes::CameraNode;

// forward Game declaration
class SampleApplication;

/*!
	Class that turns input events into application events
*/
class EventReceiver : public InputHandler
{
	private:
		SampleApplication *application;
		CameraNode *camera;

		float cameraDistance;

		bool viewingActive;

	public:
		EventReceiver(SampleApplication *application, CameraNode *camera);

		void onQuit();
		void onKeyPressed(KeyboardButton key);
		void onMouseButtonPressed(MouseButton button, Vector position);
		void onMouseButtonReleased(MouseButton button, Vector position);
		void onMouseMove(Vector relativePosition);
};

#endif
