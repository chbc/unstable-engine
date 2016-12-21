#ifndef _RENDER_ENGINE_H_
#define _RENDER_ENGINE_H_

#include <engine/systems/input/InputHandler.h>
#include <engine/scene/SceneManager.h>
#include <engine/systems/multimedia/MultimediaManager.h>
#include <engine/systems/graphics/RenderManager.h>

class MultimediaManager;

namespace sre
{

/*!
	Abstract application class.
*/
class RenderEngine
{
protected:
	SPTR<RenderManager> renderManager;
	SPTR<MultimediaManager> multimediaManager;
	SPTR<InputHandler> inputHandler;

	UPTR<SceneManager> sceneManager;

	RenderEngine();

public:
	void setEventReceiver(InputHandler *inputHandler);
	void run();
	void quit();

protected:
	virtual void onInit() =0;
	virtual void onUpdate(unsigned int){};
	virtual void onQuit(){};

private:
	bool running;

	void processInput();
	void render();
	void release();

};

} // namespace
#endif
