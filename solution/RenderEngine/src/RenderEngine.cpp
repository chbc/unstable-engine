#include "RenderEngine.h"
#include "EngineValues.h"
#include "DefaultGameValues.h"
#include "ApplicationStrategy.h"
#include "EditorStrategy.h"
#include "SingletonsManager.h"

namespace sre
{

RenderEngine* RenderEngine::instance = nullptr;

RenderEngine::RenderEngine(const std::string& applicationName, int screenWidth, int screenHeight)
    : running(true)
{
    instance = this;
    EngineValues::APPLICATION_NAME = applicationName;
    EngineValues::SCREEN_WIDTH = screenWidth;
    EngineValues::SCREEN_HEIGHT = screenHeight;

    DefaultGameValues::load();

    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    singletonsManager->init();

    this->applicationStrategy = UPTR<AExecutionStrategy>(new ApplicationStrategy);
    this->editorStrategy = UPTR<AExecutionStrategy>(new EditorStrategy);
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
    this->changeStrategy(false);

    uint32_t elapsedTime = 0;
    while (this->running)
    {
        elapsedTime = this->currentStrategy->beginFrame(this);
        this->currentStrategy->update(this, elapsedTime * 0.001f);
        this->currentStrategy->render(this);
        this->currentStrategy->swapBuffers(this);
        this->currentStrategy->endFrame(this);
        this->currentStrategy->delay(this);
    }

    this->release();
}

void RenderEngine::quit()
{
    this->running = false;
}

/*
void RenderEngine::onFrameEnd()
{
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

    // XXX CHAMAR COMANDOS QUE PRECISEM SER EXECUTADOS NO FIM DO FRAME
}
*/

void RenderEngine::loadScene(const char* sceneName)
{
    this->currentStrategy->loadScene(sceneName);
    this->currentStrategy->init(this);
}

void RenderEngine::changeStrategy(bool application)
{
    this->currentStrategy = application ? this->applicationStrategy.get() : this->editorStrategy.get();
    this->loadScene("XXX");
}

void RenderEngine::release()
{
    this->applicationStrategy->release();
    this->editorStrategy->release();

    SingletonsManager::getInstance()->release();
}

} // namespace
