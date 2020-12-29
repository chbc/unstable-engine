#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include <InputHandler.h>
#include <Entity.h>

using namespace sre;

class ScreenManager;
class SampleApplication;

/*!
	Class that turns input events into application events
*/
class EventReceiver : public InputHandler
{
	private:
		SampleApplication* application;
		ScreenManager* screenManager;

	public:
		EventReceiver(SampleApplication* arg_sampleApplication, ScreenManager* arg_screenManager);

		void onQuit() override;
		void onGUIButtonPressed(GUIButtonComponent* guiButton, const std::string& entityName) override;
};
#endif
