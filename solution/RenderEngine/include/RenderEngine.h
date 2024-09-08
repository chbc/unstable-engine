#ifndef _RENDER_ENGINE_H_
#define _RENDER_ENGINE_H_

#include "ScenesManager.h"
#include "MultimediaManager.h"
#include "RenderManager.h"
#include "EngineValues.h"
#include "WorldEditor.h"
#include <functional>

namespace sre
{

/*!
    Abstract application class.
*/
class SRE_API RenderEngine
{
protected:
    MultimediaManager* multimediaManager;
    UPTR<ScenesManager> scenesManager;
	
private:
    RenderManager* renderManager;
    CameraComponent* applicationCamera;
    bool running;
    bool isEditorMode;
    bool wasEditorMode;

#if !defined(RELEASE) && !defined(__ANDROID__)
    UPTR<WorldEditor> worldEditor;
#endif

public:
    RenderEngine(const std::string& applicationName = "Unstable Engine", int screenWidth = 1500, int screenHeight = 768);

public:
    void run();
    void loadScene(const std::string& scene);
    void TEMP_loadScene(std::function<void()>& loadFunction);
    void setEditorMode(bool value);
    void quit();

protected:
    virtual void onInit() =0;
    virtual void onUpdate(float elapsedTime) {}
    virtual void onGUI(){};
    virtual void onEditorGUI();
    virtual void onQuit(){};

private:
    void init();
    void update(float elapsedTime);
    void processMultimediaInput();
    void onEndFrame();
    void removeDestroyedEntities();
    void release();
};

} // namespace
#endif
