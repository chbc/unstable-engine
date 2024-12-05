#include "AExecutionStrategy.h"
#include "RenderEngine.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "MultimediaManager.h"
#include "ScenesManager.h"
#include "MessagesManager.h"
#include "EntityDestroyedMessage.h"

namespace sre
{

AExecutionStrategy::AExecutionStrategy() : entityDestroyed(false)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    this->renderManager = singletonsManager->get<RenderManager>();
    this->multimediaManager = singletonsManager->get<MultimediaManager>();
    this->scenesManager = singletonsManager->get<ScenesManager>();

    Action* action = new Action{ [&](void* message) { this->onEntityDestroyed(message); } };
    this->entityDestroyedAction = SPTR<Action>(action);

    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->addListener<EntityDestroyedMessage>(this->entityDestroyedAction.get());
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
        this->entityDestroyed = false;
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

void AExecutionStrategy::loadScene(const char* sceneName)
{
    std::string currentSceneName = this->scenesManager->getMainSceneName();
    std::string newSceneName{ sceneName };
    if (newSceneName.empty())
    {
        sceneName = currentSceneName.c_str();
    }

    this->multimediaManager->cleanUp();
    this->renderManager->cleanUp();
    this->scenesManager->cleanUp();

    this->scenesManager->loadScene(sceneName);

    this->renderManager->initPostProcessing();
    //
}

void AExecutionStrategy::onEntityDestroyed(void* data)
{
    this->entityDestroyed = true;
}

} // namespace
