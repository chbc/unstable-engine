#ifndef _AMULTIMEDIA_WRAPPER_H_
#define _AMULTIMEDIA_WRAPPER_H_

#include <memory>

namespace sre
{

class MultimediaManager;
class Timer;
class InputHandler;

class AMultimediaWrapper
{
	private:
		static std::unique_ptr<AMultimediaWrapper> instance;

	public:
		virtual ~AMultimediaWrapper() {}

	protected:
		AMultimediaWrapper() {}

		static AMultimediaWrapper *getInstance();
		
		virtual void init(int width, int height) =0; // throws sdl error
		virtual void swapBuffers() =0;
		virtual void processInput(InputHandler *inputHandler) =0;
		virtual bool checkClosePressed() =0;
		virtual unsigned int getTicks() =0;
		virtual void delay(unsigned int timeMS) =0;
		virtual void release() =0;

	friend class MultimediaManager;
	friend class Timer;
};

} // namespace
#endif
