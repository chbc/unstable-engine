#include "ApplicationStrategy.h"
#include "RenderEngine.h"
#include "ScenesManager.h"
#include "Input.h"
#include "MultimediaManager.h"

namespace sre
{

ApplicationStrategy::ApplicationStrategy()
{
}

void ApplicationStrategy::init(RenderEngine* controller)
{
	this->multimediaManager->setEditorMode(false);
	this->scenesManager->initEntities();
	controller->onInit();
}

void ApplicationStrategy::update(RenderEngine* controller, float elapsedTime)
{
	AExecutionStrategy::update(controller, elapsedTime);

	controller->onUpdate(elapsedTime);
	this->scenesManager->update(elapsedTime);

#ifdef DEBUG
	if (Input::isKeyJustPressed(KEY_HOME))
		controller->changeStrategy(false);
#endif
}

} // namespace
