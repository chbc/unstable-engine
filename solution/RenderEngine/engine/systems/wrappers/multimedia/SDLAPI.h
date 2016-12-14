#ifndef _SDLAPI_H_
#define _SDLAPI_H_

#include "AMultimediaWrapper.h"
#include <string>

struct SDL_Window;
union SDL_Event;

namespace sre
{

class SDLAPI : AMultimediaWrapper
{
private:
	SDL_Window *window;
	void *context;
	SDL_Event *event;

public:
	SDLAPI() {}

protected:
	void init(int width, int height) override;
	void swapBuffers() override;
	void processInput(InputHandler *inputHandler) override;
	bool checkClosePressed() override;
	unsigned int getTicks() override;
	void delay(unsigned int) override;
	void release() override;

private:
	std::string getError();
};

} // namespace sre
#endif