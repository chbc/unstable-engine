#include "EventReceiver.h"
#include "application/SampleApplication.h"
#include "application/ScreenManager.h"

EventReceiver::EventReceiver(SampleApplication* arg_application, ScreenManager* arg_screenManager)
	: application(arg_application), screenManager(arg_screenManager)
{
}

void EventReceiver::onQuit()
{
	this->application->quit();
}

void EventReceiver::onGUIButtonPressed(GUIButtonComponent* guiButton, const std::string& entityName)
{
	this->screenManager->onButtonPress(guiButton, entityName);
}
