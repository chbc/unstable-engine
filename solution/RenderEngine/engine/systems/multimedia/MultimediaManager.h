#ifndef _MULTIMEDIA_MANAGER_H_
#define _MULTIMEDIA_MANAGER_H_

#include <engine/util/singleton_macros.h>
#include <memory>

namespace sre
{

class AMultimediaWrapper;
class RenderEngine;
class InputHandler;
class Timer;

/*!
	Class for window management
*/
class MultimediaManager
{
	DECLARE_SINGLETON(MultimediaManager);

	private:
		AMultimediaWrapper *multimediaWrapper;
		std::unique_ptr<Timer> timer;

	public:
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;

	private:
		void swapBuffers();
		void processInput(InputHandler *inputHandler);
		bool checkClosePressed();
		void onBeginFrame();
		void onEndFrame();
		unsigned int getElapsedTime();

	friend class RenderEngine;
};

} // namespace

#endif
