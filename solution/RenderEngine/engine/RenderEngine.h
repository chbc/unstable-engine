#ifndef _RENDER_ENGINE_H_
#define _RENDER_ENGINE_H_

#include <engine/systems/graphics/RenderManager.h>
#include <engine/systems/graphics/TextureManager.h>
#include <engine/systems/multimedia/MultimediaManager.h>
#include <engine/systems/input/InputHandler.h>
#include <engine/systems/timer/Timer.h>
#include <engine/scene/SceneManager.h>

#include <engine/nodes/renderables/materials/DiffuseMaterial.h>

namespace sre
{

/*!
	Abstract application class.
*/
class RenderEngine
{
	private:
		bool running;

		void processInput();
		void render();
		void release();

	protected:
		RenderManager *renderManager;
		MultimediaManager *multimediaManager;
		InputHandler *inputHandler;
		SceneManager *sceneManager;

		RenderEngine();

		virtual void onInit() =0;
		virtual void onUpdate(unsigned int){};
		virtual void onQuit(){};

	public:
		void registerEventReceiver(InputHandler *inputHandler);
		void run();
		void quit();
};

} // namespace
#endif
