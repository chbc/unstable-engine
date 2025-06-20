#include "AExecutionStrategy.h"
#include "RenderEngine.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "MultimediaManager.h"
#include "ScenesManager.h"
#include "MessagesManager.h"
#include "EntityDestroyedMessage.h"
#include "Log.h"

namespace sre
{

AExecutionStrategy::AExecutionStrategy() : entityDestroyed(false)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    this->renderManager = singletonsManager->get<RenderManager>();
    this->multimediaManager = singletonsManager->get<MultimediaManager>();
    this->scenesManager = singletonsManager->get<ScenesManager>();
}

void AExecutionStrategy::init(RenderEngine* controller)
{
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

void AExecutionStrategy::cleanUp()
{
    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->removeListener<EntityDestroyedMessage>(this->entityDestroyedAction.get());
}

void AExecutionStrategy::loadScene(const char* scenePath)
{
    this->renderManager->cleanUpMeshes();
    this->scenesManager->loadScene(scenePath);
    this->renderManager->initPostProcessing();
}

void AExecutionStrategy::loadGuiScene(const char* guiScenePath)
{
    this->multimediaManager->cleanUp();
    this->renderManager->cleanUpGui();
	this->scenesManager->loadGuiScene(guiScenePath);
}

void AExecutionStrategy::onEntityDestroyed(void* data)
{
    this->entityDestroyed = true;
}

} // namespace
