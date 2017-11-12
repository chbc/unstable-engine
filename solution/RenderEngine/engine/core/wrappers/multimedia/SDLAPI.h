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

public:
	SDLAPI() {}

protected:
	void init(float width, float height, const std::string &title) override;
	void swapBuffers() override;
	void processInput(InputHandler *inputHandler) override;
	bool checkClosePressed() override;
	unsigned int getTicks() override;
	void delay(unsigned int) override;
	void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp) override;
	void release() override;

private:
	std::string getError();
};

} // namespace sre
#endif
