#include "RenderEngine.h"
#include "SingletonsManager.h"

namespace sre
{

RenderEngine::RenderEngine(const std::string& applicationName, int screenWidth, int screenHeight)
{
    EngineValues::APPLICATION_NAME = applicationName;
    EngineValues::SCREEN_WIDTH = screenWidth;
    EngineValues::SCREEN_HEIGHT = screenHeight;
}

void RenderEngine::run()
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    this->renderManager = singletonsManager->resolve<RenderManager>();
    this->multimediaManager = singletonsManager->resolve<MultimediaManager>();

    this->multimediaManager->init();
    this->renderManager->init();
	this->sceneManager = UPTR<SceneManager>{ new SceneManager };
	this->guiManager = UPTR<GUIManager>{ new GUIManager };

#if defined(DEBUG) && !defined(__ANDROID__)
    this->worldEditor = UPTR<WorldEditor>{ new WorldEditor };
#endif

    this->onInit();

    this->guiManager->onSceneLoaded();
    this->sceneManager->onSceneLoaded();
    this->renderManager->onSceneLoaded();

#if defined(DEBUG) && !defined(__ANDROID__)
    this->worldEditor->init(this->sceneManager.get());
#endif

    this->isEditorMode = false;
    this->running = true;
    uint32_t elapsedTime = 0;
    while(this->running)
    {
        this->multimediaManager->onBeginFrame();

        this->processInput();
        this->onUpdate(this->multimediaManager->getLastFrameTime());
    	
        this->renderManager->render();
        this->onGUI();
        this->onEditorGUI();

    	this->multimediaManager->swapBuffers();

        this->removeDestroyedEntities();
        elapsedTime = this->multimediaManager->stopTimer();

#ifdef DEBUG
        this->guiManager->updateFrameIndicator(elapsedTime);
#endif

        this->multimediaManager->onEndFrame();
    }
    
    this->release();
}

void RenderEngine::onEditorGUI()
{
#if defined(DEBUG) && !defined(__ANDROID__)
    if (this->isEditorMode)
        this->worldEditor->onGUI(&this->isEditorMode);
#endif
}

void RenderEngine::release()
{
    SingletonsManager::getInstance()->release();
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
    this->guiManager->removeDestroyedEntities();
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
