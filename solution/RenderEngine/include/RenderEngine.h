#pragma once

#include "AExecutionStrategy.h"
#include "memory_aliases.h"
#include "core_defines.h"
#include <string>

namespace sre
{

class SRE_API RenderEngine
{
private:
    bool running;
    UPTR<AExecutionStrategy> applicationStrategy;
    UPTR<AExecutionStrategy> editorStrategy;
    AExecutionStrategy* currentStrategy;

    static RenderEngine* instance;

public:
    RenderEngine(const std::string& applicationName = "Unstable Engine", int screenWidth = 1500, int screenHeight = 768);

public:
    static RenderEngine* getInstance();
    void run();
    void quit();
    void loadScene(const char* sceneName);

protected:
    virtual void onInit() =0;
    virtual void onUpdate(float elapsedTime) {}
    virtual void onGUI() {}
    virtual void onEditorGUI() {}
    virtual void onQuit() {};

private:
    void changeStrategy(bool application);
    void release();

friend class AExecutionStrategy;
friend class ApplicationStrategy;
friend class EditorStrategy;
};

} // namespace
