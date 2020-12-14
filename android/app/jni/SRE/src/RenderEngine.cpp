#include "RenderEngine.h"

namespace sre
{

RenderEngine::RenderEngine()
{
    this->singletonsManager = SingletonsManager::getInstance();

    this->renderManager = this->singletonsManager->resolve<RenderManager>();
    this->multimediaManager = this->singletonsManager->resolve<MultimediaManager>();
}

void RenderEngine::run()
{
    this->multimediaManager->init();
    this->renderManager->init();
	this->sceneManager = UPTR<SceneManager>{ new SceneManager };
	// ### this->guiManager = UPTR<GUIManager>{ new GUIManager };

	this->multimediaManager->logMessage("XXX RenderManager - run 1");

    this->onInit();

    // ### this->guiManager->onSceneLoaded();

	this->multimediaManager->logMessage("XXX RenderManager - run 2");
    this->sceneManager->onSceneLoaded();
	this->multimediaManager->logMessage("XXX RenderManager - run 3");
    this->renderManager->onSceneLoaded();
	this->multimediaManager->logMessage("XXX RenderManager - run 4");

    this->running = true;
    uint32_t elapsedTime = 0;
    while(this->running)
    {
        this->multimediaManager->onBeginFrame();

        this->processInput();
        this->onUpdate(this->multimediaManager->getLastFrameTime());
        this->render();

        this->removeDestroyedEntities();
        elapsedTime = this->multimediaManager->stopTimer();

#ifdef DEBUG
        // ### this->guiManager->updateFrameIndicator(elapsedTime);
#endif

        this->multimediaManager->onEndFrame();
    }
    
    this->release();
}

void RenderEngine::release()
{
    this->singletonsManager->release();
}

void RenderEngine::processInput()
{
	InputHandler* inputHandlerPtr = inputHandler.get();
    if (inputHandlerPtr != nullptr)
        this->multimediaManager->processInput(inputHandlerPtr);
    else
        this->running = !this->multimediaManager->checkClosePressed();
}

void RenderEngine::removeDestroyedEntities()
{
    this->renderManager->removeDestroyedEntities();
    this->sceneManager->removeDestroyedEntities();
    // XXX this->guiManager->removeDestroyedEntities();
}

void RenderEngine::render()
{
    this->renderManager->render();
    this->onGUI();
    this->multimediaManager->swapBuffers();
}

void RenderEngine::setEventReceiver(InputHandler *inputHandler)
{
	this->inputHandler = UPTR<InputHandler>{ inputHandler };
}

void RenderEngine::quit()
{
    this->running = false;
}

} // namespace
