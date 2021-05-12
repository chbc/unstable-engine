#include "RenderEngine.h"
#include "SingletonsManager.h"
#include "DefaultGameValues.h"

namespace sre
{

RenderEngine::RenderEngine(const std::string& applicationName, int screenWidth, int screenHeight)
{
    EngineValues::APPLICATION_NAME = applicationName;
    EngineValues::SCREEN_WIDTH = screenWidth;
    EngineValues::SCREEN_HEIGHT = screenHeight;

    DefaultGameValues::load();
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
    this->worldEditor = UPTR<WorldEditor>( new WorldEditor{ this->sceneManager.get(), &this->isEditorMode });
#endif

    this->onInit();

    this->guiManager->onSceneLoaded();
    this->sceneManager->onSceneLoaded();
    this->renderManager->onSceneLoaded();

    this->isEditorMode = false;
    this->wasEditorMode = false;
    this->running = true;
    uint32_t elapsedTime = 0;
    while (this->running)
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

        this->onEndFrame();
    }
    
    this->release();
}

void RenderEngine::setEventReceiver(InputHandler* inputHandler)
{
    this->inputHandler = UPTR<InputHandler>{ inputHandler };
}

void RenderEngine::loadScene(const std::string& scene)
{
    this->guiManager->destroyAllEntities();
    this->sceneManager->destroyAllEntities();

    this->removeDestroyedEntities();

    this->onInit();

    this->guiManager->onSceneLoaded();
    this->sceneManager->onSceneLoaded();
    this->renderManager->onSceneLoaded();
}

void RenderEngine::toggleEditorMode()
{
    this->isEditorMode = !this->isEditorMode;
}

void RenderEngine::quit()
{
    this->running = false;
}

void RenderEngine::onEditorGUI()
{
#if defined(DEBUG) && !defined(__ANDROID__)
    if (this->isEditorMode && this->wasEditorMode)
        this->worldEditor->onEditorGUI();
#endif
}

void RenderEngine::processInput()
{
	InputHandler* inputHandlerPtr = inputHandler.get();
    if (inputHandlerPtr != nullptr)
        this->multimediaManager->processInput(inputHandlerPtr);
    else
        this->running = !this->multimediaManager->checkClosePressed();
}

void RenderEngine::onEndFrame()
{
    this->multimediaManager->onEndFrame();
    if (this->isEditorMode != this->wasEditorMode)
    {
        this->wasEditorMode = this->isEditorMode;
        this->multimediaManager->setEditorMode(this->isEditorMode);

        if (this->isEditorMode)
            this->worldEditor->init();
        else
            this->worldEditor->release();
    }
}

void RenderEngine::removeDestroyedEntities()
{
    this->renderManager->onRemoveDestroyedEntities();
    this->multimediaManager->onRemoveDestroyedEntities();
    this->sceneManager->removeDestroyedEntities();
    this->guiManager->removeDestroyedEntities();
}

void RenderEngine::release()
{
    SingletonsManager::getInstance()->release();

    this->sceneManager->release();
}

} // namespace
