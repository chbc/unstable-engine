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
		SampleApplication* application;

	public:
		EventReceiver(SampleApplication* arg_sampleApplication);

		void onQuit() override;
		void onGUIButtonPressed(GUIButtonComponent* guiButton, const std::string& entityName) override;
};
#endif
