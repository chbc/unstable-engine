#ifndef _AMULTIMEDIA_WRAPPER_H_
#define _AMULTIMEDIA_WRAPPER_H_

#include <string>
#include "memory_aliases.h"

namespace sre
{

class InputHandler;
class GUIButtonComponent;

class AMultimediaWrapper
{
protected:
	AMultimediaWrapper() = default;

public:	
	virtual ~AMultimediaWrapper() = default;

protected:
	virtual void init() =0; // throws sdl error
	virtual void swapBuffers() =0;
	virtual void processInput(InputHandler* inputHandler, const std::vector<GUIButtonComponent*>& guiButtons) =0;
	virtual bool checkClosePressed() =0;
	virtual unsigned int getTicks() =0;
	virtual void delay(unsigned int timeMS) =0;
	virtual void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp) =0;
	virtual void log(const std::string& type, const std::string& message) =0;
	virtual void release() =0;

friend class MultimediaManager;
friend class Timer;
};

} // namespace
#endif
