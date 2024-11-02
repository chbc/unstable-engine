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
    this->currentStrategy = this->applicationStrategy.get();
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
    this->currentStrategy->loadScene("default");
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

    this->release();
}

void RenderEngine::quit()
{
    this->running = false;
}

void RenderEngine::loadScene(const char* sceneName)
{
    std::function<void(void)> action = [&]
    {
        this->currentStrategy->loadScene(sceneName);
        this->currentStrategy->init(this);
    };
    endFrameActions.emplace(action);
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
        this->currentStrategy = (mode == EExecutionMode::APPLICATION) ? this->applicationStrategy.get() : this->editorStrategy.get();
    };
    endFrameActions.emplace(action);

    this->loadScene("default");
}

void RenderEngine::release()
{
    this->applicationStrategy->release();
    this->editorStrategy->release();

    SingletonsManager::getInstance()->release();
}

} // namespace
