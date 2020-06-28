#ifndef _RENDER_ENGINE_H_
#define _RENDER_ENGINE_H_

#include "InputHandler.h"
#include "SceneManager.h"
#include "GUIManager.h"
#include "MultimediaManager.h"
#include "RenderManager.h"
#include "SingletonsManager.h"

class MultimediaManager;

namespace sre
{

/*!
    Abstract application class.
*/
class SRE_API RenderEngine
{
protected:
    SingletonsManager* singletonsManager;
    RenderManager* renderManager;
    MultimediaManager* multimediaManager;
    UPTR<SceneManager> sceneManager;
	UPTR<GUIManager> guiManager;
	UPTR <InputHandler> inputHandler;

    RenderEngine();

public:
    void setEventReceiver(InputHandler *inputHandler);
    void run();
    void quit();

protected:
    virtual void onInit() =0;
    virtual void onUpdate(unsigned int){};
    virtual void onGUI(){};
    virtual void onQuit(){};

private:
    bool running;

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
