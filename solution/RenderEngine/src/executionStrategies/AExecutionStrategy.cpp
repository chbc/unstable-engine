#include "AExecutionStrategy.h"
#include "RenderEngine.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "MultimediaManager.h"
#include "ScenesManager.h"
#include "Log.h"

namespace sre
{

AExecutionStrategy::AExecutionStrategy()
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    this->renderManager = singletonsManager->get<RenderManager>();
    this->multimediaManager = singletonsManager->get<MultimediaManager>();
    this->scenesManager = singletonsManager->get<ScenesManager>();
}

uint32_t AExecutionStrategy::beginFrame(RenderEngine* controller)
{
    this->multimediaManager->onFrameBegin();
    return this->multimediaManager->getLastFrameTime();
}

void AExecutionStrategy::update(RenderEngine* controller, float elapsedTime)
{
    this->multimediaManager->processInput();
    controller->running = !this->multimediaManager->checkClosePressed();
}

void AExecutionStrategy::render(RenderEngine* controller)
{
    this->renderManager->render();
    controller->onGUI();
}

void AExecutionStrategy::swapBuffers(RenderEngine* controller)
{
    this->multimediaManager->swapBuffers();
}

inline void AExecutionStrategy::endFrame(RenderEngine* controller)
{
	this->scenesManager->onEndFrame();
}

void AExecutionStrategy::delay(RenderEngine* controller)
{
    uint32_t elapsedTime = this->multimediaManager->stopTimer();

#ifdef DEBUG
    GUIScene::updateFrameIndicator(elapsedTime);
#endif

    this->multimediaManager->delay();
}

void AExecutionStrategy::reloadScenes()
{
    this->scenesManager->reloadScenes();
    this->renderManager->initPostProcessing();
}

void AExecutionStrategy::loadScene(const char* scenePath)
{
    this->scenesManager->loadScene(scenePath);
    this->renderManager->initPostProcessing();
}

void AExecutionStrategy::loadGuiScene(const char* guiScenePath)
{
    this->multimediaManager->cleanUp();
    this->renderManager->cleanUpGui();
	this->scenesManager->loadGuiScene(guiScenePath);
}

} // namespace
