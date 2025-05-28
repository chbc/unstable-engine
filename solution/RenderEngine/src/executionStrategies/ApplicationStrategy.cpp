#include "ApplicationStrategy.h"
#include "RenderEngine.h"
#include "ScenesManager.h"
#include "MultimediaManager.h"
#include "RenderManager.h"
#include "Input.h"

namespace sre
{

ApplicationStrategy::ApplicationStrategy()
{
}

void ApplicationStrategy::init(RenderEngine* controller)
{
	AExecutionStrategy::init(controller);

	this->multimediaManager->setExecutionMode(EExecutionMode::APPLICATION);
	this->renderManager->setExecutionMode(EExecutionMode::APPLICATION);
	this->renderManager->setTargetFBO(0);
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
		controller->changeStrategy(EExecutionMode::EDITOR);
#endif
}

} // namespace
