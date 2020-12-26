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

protected:
    RenderEngine() = default;
    RenderEngine(const std::string& applicationName, int screenWidth, int screenHeight);

public:
    virtual ~RenderEngine() = default;
    void setEventReceiver(InputHandler *inputHandler);
    void run();
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
