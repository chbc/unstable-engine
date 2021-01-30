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

public:
    RenderEngine(const std::string& applicationName = "Unstable Engine", int screenWidth = 800, int screenHeight = 600);

public:
    virtual ~RenderEngine() = default;
    void run();
    void setEventReceiver(InputHandler *inputHandler);
    void loadScene(const std::string& scene);
    void quit();

protected:
    virtual void onInit() =0;
    virtual void onUpdate(unsigned int){};
    virtual void onGUI(){};
    virtual void onEditorGUI();
    virtual void onQuit(){};

private:
#if defined(DEBUG) && !defined(__ANDROID__)
    UPTR<WorldEditor> worldEditor;
#endif
    bool running;
    bool isEditorMode;

    void processInput();
    void removeDestroyedEntities();
    void release();

	template <typename T>
	void safeDelete(T* pointer)
	{
		if (pointer != nullptr)
			delete pointer;
	}

};

} // namespace
#endif
