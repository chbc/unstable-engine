#ifndef _RENDER_ENGINE_H_
#define _RENDER_ENGINE_H_

#include "InputHandler.h"
#include "SceneManager.h"
#include "GUIManager.h"
#include "MultimediaManager.h"
#include "RenderManager.h"
#include "EngineValues.h"

#if defined(DEBUG) && !defined(__ANDROID__)
#include "WorldEditor.h"
#endif

namespace sre
{

/*!
    Abstract application class.
*/
class SRE_API RenderEngine
{
public:
    MultimediaManager* multimediaManager;
    UPTR<SceneManager> sceneManager;
	UPTR<GUIManager> guiManager;
	UPTR <InputHandler> inputHandler;
	
private:
    RenderManager* renderManager;
    bool running;
    bool isEditorMode;
    bool wasEditorMode;

#if defined(DEBUG) && !defined(__ANDROID__)
    UPTR<WorldEditor> worldEditor;
#endif

public:
    RenderEngine(const std::string& applicationName = "Unstable Engine", int screenWidth = 1024, int screenHeight = 768);

public:
    virtual ~RenderEngine() = default;
    void run();
    void setEventReceiver(InputHandler *inputHandler);
    void loadScene(const std::string& scene);
    void toggleEditorMode();
    void quit();

protected:
    virtual void onInit() =0;
    virtual void onUpdate(unsigned int){};
    virtual void onGUI(){};
    virtual void onEditorGUI();
    virtual void onQuit(){};

private:
    void processInput();
    void onEndFrame();
    void removeDestroyedEntities();
    void release();
};

} // namespace
#endif
