#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include <CameraComponent.h>
#include <PostProcessingEffect.h>

using namespace sre;

class SampleApplication;

class EventReceiver
{
private:
	SampleApplication *application;
	CameraComponent *camera;

public:
	EventReceiver(SampleApplication *application, CameraComponent *camera);

	void processInput();

private:
	void processKeys();
	void processMouse();
};
#endif
