#include "RenderEngine.h"
#include "EngineValues.h"
#include "DefaultGameValues.h"
#include "ApplicationStrategy.h"
#include "EditorStrategy.h"
#include "SingletonsManager.h"
#include "Log.h"

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
    try
    {
        this->loadSystems();

        this->applicationStrategy = UPTR<AExecutionStrategy>(new ApplicationStrategy);
        this->editorStrategy = UPTR<AExecutionStrategy>(new EditorStrategy);
        this->currentStrategy = this->editorStrategy.get();

        std::string startUpSceneName = DefaultGameValues::get<std::string>("STARTUP_SCENE");
        this->currentStrategy->loadScene(startUpSceneName.c_str());
        this->currentStrategy->init(this);

        uint32_t elapsedTime = 0;
        while (this->running)
        {
            elapsedTime = this->currentStrategy->beginFrame(this);
            this->currentStrategy->update(this, elapsedTime * 0.001f);
            this->currentStrategy->render(this);
            this->currentStrategy->swapBuffers(this);
            this->currentStrategy->endFrame(this);

            this->dispatchEndFrameActions();
            this->currentStrategy->delay(this);
        }

    }
    catch (std::string& message)
    {
        onError(message);
    }
    
    this->release();
}

void RenderEngine::quit()
{
    this->running = false;
}

void RenderEngine::loadScene(std::string sceneName)
{
    std::function<void(void)> action = [=]
    {
        this->currentStrategy->loadScene(sceneName.c_str());
        this->currentStrategy->init(this);
    };
    endFrameActions.emplace(action);
}

void RenderEngine::onError(const std::string& message)
{
    Log::showErrorMessageBox("Error", message);
}

void RenderEngine::loadSystems()
{
    DefaultGameValues::load();
    SingletonsManager* singletonsManager = SingletonsManager::loadInstance();
    singletonsManager->init();
}

void RenderEngine::dispatchEndFrameActions()
{
    while (!this->endFrameActions.empty())
    {
        const std::function<void(void)>& action = endFrameActions.front();
        action();
        endFrameActions.pop();
    }
}

void RenderEngine::changeStrategy(const EExecutionMode::Type mode)
{
    std::function<void(void)> action = [=]
    {
        this->currentStrategy->cleanUp();
        this->currentStrategy = (mode == EExecutionMode::APPLICATION) ? this->applicationStrategy.get() : this->editorStrategy.get();
    };
    endFrameActions.emplace(action);

    this->loadScene();
}

void RenderEngine::release()
{
    if (SingletonsManager::isInitialized())
    {
        if (this->applicationStrategy != nullptr)
        {
            this->applicationStrategy->release();
        }

        if (this->editorStrategy != nullptr)
        {
            this->editorStrategy->release();
        }

        SingletonsManager::getInstance()->release();
    }
}

} // namespace
