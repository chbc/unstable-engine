#ifndef _RENDER_ENGINE_H_
#define _RENDER_ENGINE_H_

#include <engine/core/io/InputHandler.h>
#include <engine/entitiesManagers/scene/SceneManager.h>
#include <engine/entitiesManagers/gui/GUIManager.h>
#include <engine/core/multimedia/MultimediaManager.h>
#include <engine/core/graphics/RenderManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>

class MultimediaManager;

namespace sre
{

/*!
    Abstract application class.
*/
class SRE_API RenderEngine
{
protected:
    SingletonsManager *singletonsManager;
    RenderManager *renderManager;
    MultimediaManager *multimediaManager;
    UPTR<InputHandler> inputHandler;
    UPTR<SceneManager> sceneManager;
    UPTR<GUIManager> guiManager;

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

    void render();
    void release();

};

} // namespace
#endif
