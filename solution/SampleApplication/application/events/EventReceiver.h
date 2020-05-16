#ifndef _EVENT_RECEIVER_H_
#define _EVENT_RECEIVER_H_

#include <InputHandler.h>
#include <CameraComponent.h>
#include <PostProcessingEffect.h>

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
	PostProcessingEffect* ppEffect;

	float effectValue;

public:
	EventReceiver(SampleApplication *application, CameraComponent *camera, PostProcessingEffect* effect);

	void onQuit() override;
	void onKeyPressed(KeyboardButton key) override;
	void onMouseButtonPressed(MouseButton mouseButton, const glm::vec2 &position) override;
	void onMouseButtonReleased(MouseButton mouseButton, const glm::vec2 &position) override;
	void onMouseMoveRelative(const glm::vec2 &relativePosition) override;
	void onMouseWheel(int direction) override;
};
#endif
