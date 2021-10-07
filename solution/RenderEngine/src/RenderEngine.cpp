#include "RenderEngine.h"
#include "SingletonsManager.h"
#include "DefaultGameValues.h"
#include "EditorMessages.h"
#include "MessagesManager.h"

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
    this->init();

    uint32_t elapsedTime = 0;
    while (this->running)
    {
        this->multimediaManager->onBeginFrame();

        this->processInput();

        if (!this->isEditorMode)
            this->onUpdate(this->multimediaManager->getLastFrameTime());
    	
        this->renderManager->render();
        this->onGUI();
        this->renderManager->unbindFrameBuffer();
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

void RenderEngine::setEditorMode(bool value)
{
    this->isEditorMode = value;
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

void RenderEngine::init()
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    this->renderManager = singletonsManager->resolve<RenderManager>();
    this->multimediaManager = singletonsManager->resolve<MultimediaManager>();

    this->multimediaManager->init();
    this->renderManager->init();
    this->sceneManager = UPTR<SceneManager>{ new SceneManager };
    this->guiManager = UPTR<GUIManager>{ new GUIManager };

#if !defined(RELEASE) && !defined(__ANDROID__)
    this->worldEditor = UPTR<WorldEditor>(new WorldEditor{ this->sceneManager.get() });
#endif

    this->onInit();

    this->guiManager->onSceneLoaded();
    this->sceneManager->onSceneLoaded();
    this->renderManager->onSceneLoaded();

    this->isEditorMode = false;
    this->wasEditorMode = false;
    this->running = true;

    MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
    Action action = [&](void* message) { this->setEditorMode(false); };
    messagesManager->addListener<ExitEditorMessage>(action);
}

void RenderEngine::processInput()
{
    this->multimediaManager->processInput();
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
        {
            this->applicationCamera = this->renderManager->getMainCamera();
            this->worldEditor->init();
        }
        else
        {
            this->worldEditor->release();
            this->renderManager->setMainCamera(this->applicationCamera);
        }
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
