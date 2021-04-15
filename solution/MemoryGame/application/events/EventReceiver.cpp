#include "EventReceiver.h"
#include "application/SampleApplication.h"

EventReceiver::EventReceiver(SampleApplication* arg_application) : application(arg_application)
{
}

void EventReceiver::onQuit()
{
	this->application->quit();
}

void EventReceiver::onGUIButtonPressed(GUIButtonComponent* guiButton, const std::string& entityName)
{
	this->application->onButtonPress(guiButton, entityName);
}
