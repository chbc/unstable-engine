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

RenderEngine::RenderEngine()
    : running(true)
{
	if (instance != nullptr)
	{
		throw "[RenderEngine] instance already exists!";
	}

    instance = this;
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

        std::string startUpScenePath = DefaultGameValues::get<std::string>("STARTUP_SCENE");
        std::string startUpGuiScenePath = DefaultGameValues::get<std::string>("STARTUP_GUI_SCENE");
        this->currentStrategy->loadScene(startUpScenePath.c_str());
		this->currentStrategy->loadGuiScene(startUpGuiScenePath.c_str());
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

        this->onQuit();
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

void RenderEngine::loadScene(std::string scenePath)
{
    std::function<void(void)> action = [=]
    {
        this->currentStrategy->cleanUp();
        this->currentStrategy->loadScene(scenePath.c_str());
        this->currentStrategy->init(this);
    };
    endFrameActions.emplace(action);
}

void RenderEngine::loadGuiScene(std::string guiScenePath)
{
	std::function<void(void)> action = [=]
	{
		this->currentStrategy->loadGuiScene(guiScenePath.c_str());
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

    EngineValues::APPLICATION_NAME = DefaultGameValues::get<std::string>("APPLICATION_NAME");
    EngineValues::SCREEN_WIDTH = DefaultGameValues::get<int>("SCREEN_WIDTH");
    EngineValues::SCREEN_HEIGHT = DefaultGameValues::get<int>("SCREEN_HEIGHT");

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
        this->currentStrategy->init(this);
    };
    endFrameActions.emplace(action);

    // XXX this->loadScenes();
}

void RenderEngine::release()
{
    if (SingletonsManager::isInitialized())
    {
        if (this->applicationStrategy != nullptr)
        {
            this->applicationStrategy->cleanUp();
            this->applicationStrategy->release();
        }

        if (this->editorStrategy != nullptr)
        {
            this->editorStrategy->cleanUp();
            this->editorStrategy->release();
        }

        SingletonsManager::getInstance()->release();
    }
}

} // namespace
