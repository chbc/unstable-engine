#pragma once

#include "AExecutionStrategy.h"
#include "memory_aliases.h"
#include "core_defines.h"
#include <string>
#include "EExecutionMode.h"
#include <queue>
#include <functional>

namespace sre
{

class SRE_API RenderEngine
{
private:
    bool running{ true };
    UPTR<AExecutionStrategy> applicationStrategy;
    UPTR<AExecutionStrategy> editorStrategy;
    AExecutionStrategy* currentStrategy{ nullptr };
    std::queue<std::function<void(void)>> endFrameActions;

    static RenderEngine* instance;

public:
    RenderEngine();

public:
    static RenderEngine* getInstance();
    void run();
    void quit();
    void loadScene(std::string scenePath);
    void loadGuiScene(std::string guiScenePath);

protected:
    virtual void onInit() =0;
    virtual void onInitEditor() {}
    virtual void onUpdate(float elapsedTime) {}
    virtual void onGUI() {}
    virtual void onEditorGUI() {}
    virtual void onQuit() {}
    virtual void onError(const std::string& message);

private:
    void loadSystems();
    void dispatchEndFrameActions();
    void changeStrategy(const EExecutionMode::Type mode);
    void release();

friend class AExecutionStrategy;
friend class ApplicationStrategy;
friend class EditorStrategy;
};

} // namespace
