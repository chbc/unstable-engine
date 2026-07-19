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

class RenderEngine
{
private:
    bool running{ true };
    UPTR<AExecutionStrategy> applicationStrategy;
    UPTR<AExecutionStrategy> editorStrategy;
    AExecutionStrategy* currentStrategy{ nullptr };
    std::queue<std::function<void(void)>> endFrameActions;

    static RenderEngine* instance;

public:
    SRE_API RenderEngine();
    SRE_API virtual ~RenderEngine() { }

public:
    SRE_API static RenderEngine* getInstance();
    SRE_API void run();
    SRE_API void quit();
    SRE_API void loadScene(const std::string& scenePath);
    SRE_API void loadGuiScene(const std::string& guiScenePath);

protected:
    SRE_API virtual void onInit() =0;
    SRE_API virtual void onInitEditor() {}
    SRE_API virtual void onUpdate(float elapsedTime) {}
    SRE_API virtual void onGUI() {}
    SRE_API virtual void onEditorGUI() {}
    SRE_API virtual void onQuit() {}
    SRE_API virtual void onError(const std::string& message);

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
