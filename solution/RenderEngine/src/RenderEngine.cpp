#include "RenderEngine.h"
#include "SingletonsManager.h"
#include "DefaultGameValues.h"
#include "EditorMessages.h"
#include "MessagesManager.h"
#include "GUIScene.h"
#include "RenderManager.h"
#include "SceneLoader.h"

namespace sre
{

RenderEngine* RenderEngine::instance = nullptr;

RenderEngine::RenderEngine(const std::string& applicationName, int screenWidth, int screenHeight)
{
    instance = this;
    EngineValues::APPLICATION_NAME = applicationName;
    EngineValues::SCREEN_WIDTH = screenWidth;
    EngineValues::SCREEN_HEIGHT = screenHeight;

    DefaultGameValues::load();
}

RenderEngine* RenderEngine::getInstance()
{
    if (instance == nullptr)
    {
        throw "[RenderEngine] instance is null!";
    }

    return instance;
}

void RenderEngine::run()
{
    this->init();

    uint32_t elapsedTime = 0;
    float elapsedSeconds = 0.0f;
    while (this->running)
    {
        this->multimediaManager->onBeginFrame();

        this->processMultimediaInput();

        elapsedTime = this->multimediaManager->getLastFrameTime();
        elapsedSeconds = elapsedTime * 0.001f;
        if (this->isEditorMode)
            this->worldEditor->onUpdate(elapsedSeconds);
        else
            this->update(elapsedSeconds);
    	
        this->renderManager->render();
        this->onGUI();
        this->renderManager->unbindFrameBuffer();
        this->onEditorGUI();

    	this->multimediaManager->swapBuffers();

        this->removeDestroyedEntities();
        elapsedTime = this->multimediaManager->stopTimer();

#ifdef DEBUG
        GUIScene::updateFrameIndicator(elapsedTime);
#endif

        this->onEndFrame();
    }
    
    this->release();
}

void RenderEngine::loadScene(const char* sceneName)
{
    this->loadScene(sceneName, false);
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
    this->scenesManager = UPTR<ScenesManager>{ new ScenesManager };

#if !defined(RELEASE) && !defined(__ANDROID__)
    this->worldEditor = UPTR<WorldEditor>(new WorldEditor{ this->scenesManager.get() });
#endif

    this->onInit();

    this->scenesManager->loadStartUpScene();
    this->renderManager->onSceneLoaded();

    this->isEditorMode = false;
    this->wasEditorMode = false;
    this->running = true;

    MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
    Action action = [&](void* message) { this->setEditorMode(false); };
    messagesManager->addListener<ExitEditorMessage>(action);
}

void RenderEngine::update(float elapsedTime)
{
    this->onUpdate(elapsedTime);
    this->scenesManager->update(elapsedTime);

    if (Input::isKeyJustPressed(KEY_HOME))
        this->setEditorMode(true);
}

void RenderEngine::processMultimediaInput()
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
            this->worldEditor->init();
        }
        else
        {
            this->worldEditor->release();
        }

        this->renderManager->setEditorMode(this->isEditorMode);
    }
}

void RenderEngine::loadEditorScene(const char* sceneName)
{
    this->loadScene(sceneName, true);
}

void RenderEngine::loadScene(const char* sceneName, bool isEditorMode)
{
    this->scenesManager->destroyAllEntities();
    this->removeDestroyedEntities();

    Scene* scene = this->scenesManager->createScene("test_scene");
    SceneLoader::load(scene, sceneName);

    this->renderManager->setEditorMode(isEditorMode);

    this->scenesManager->onScenesLoaded();
    this->renderManager->onSceneLoaded();
}

void RenderEngine::removeDestroyedEntities()
{
    this->renderManager->onRemoveDestroyedEntities();
    this->multimediaManager->onRemoveDestroyedEntities();
    this->scenesManager->removeDestroyedEntities();
}

void RenderEngine::release()
{
    SingletonsManager::getInstance()->release();

    this->scenesManager->release();
}

} // namespace
