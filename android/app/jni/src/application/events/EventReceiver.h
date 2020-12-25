#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include <InputHandler.h>
#include <Entity.h>

using namespace sre;

class SampleApplication;

/*!
	Class that turns input events into application events
*/
class EventReceiver : public InputHandler
{
	private:
		SampleApplication *application;
		Entity *entity;

		bool isScreenPressed;

	public:
		EventReceiver(SampleApplication *arg_application, Entity *arg_entity);

		void onQuit() override;
		void onMouseButtonEvent(MouseButton mouseButton, const glm::vec2 &position, bool pressed) override;
		void onMouseMove(const glm::vec2 &position) override;
};
#endif
