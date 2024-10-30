#include "AExecutionStrategy.h"
#include "RenderEngine.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "MultimediaManager.h"
#include "ScenesManager.h"

namespace sre
{

AExecutionStrategy::AExecutionStrategy() : entityDestroyed(false)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    this->renderManager = singletonsManager->get<RenderManager>();
    this->multimediaManager = singletonsManager->get<MultimediaManager>();
    this->scenesManager = singletonsManager->get<ScenesManager>();
}

float AExecutionStrategy::beginFrame(RenderEngine* controller)
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
    this->renderManager->unbindFrameBuffer();
}

void AExecutionStrategy::swapBuffers(RenderEngine* controller)
{
    this->multimediaManager->swapBuffers();
}

void AExecutionStrategy::endFrame(RenderEngine* controller)
{
    if (this->entityDestroyed)
    {
        this->renderManager->removeDestroyedEntities();
        this->multimediaManager->removeDestroyedEntities();
        this->scenesManager->removeDestroyedEntities();
    }
}

void AExecutionStrategy::delay(RenderEngine* controller)
{
    uint32_t elapsedTime = this->multimediaManager->stopTimer();

#ifdef DEBUG
    GUIScene::updateFrameIndicator(elapsedTime);
#endif

    this->multimediaManager->delay();
}

void AExecutionStrategy::loadScene(const char* fileName)
{
    this->multimediaManager->clearButtons();
    this->renderManager->destroyAllMeshes();
    this->scenesManager->destroyAllEntities();

    this->scenesManager->loadScene("default");

    this->renderManager->initRenderers();
    this->renderManager->initPostProcessing();
    //
}

} // namespace
