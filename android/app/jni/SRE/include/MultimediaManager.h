#ifndef _MULTIMEDIA_MANAGER_H_
#define _MULTIMEDIA_MANAGER_H_

#include <glm/vec2.hpp>
#include "memory_aliases.h"
#include "ASingleton.h"

namespace sre
{

class AMultimediaWrapper;
class InputHandler;
class Timer;

/*!
	Class for window management
*/
class MultimediaManager : public ASingleton
{
private:
	UPTR<AMultimediaWrapper> multimediaWrapper;
	UPTR<Timer> timer;

	float screenWidth;
	float screenHeight;
	float aspectRatio;

private:
    MultimediaManager();

protected:
    void init() override;
    void release() override;

public:
	inline float getScreenWidth() { return this->screenWidth; }
	inline float getScreenHeight() { return this->screenHeight; }
	inline float getAspectRatio() { return this->aspectRatio; }

	float getNormalizedWidth(float pixelWidth);
	glm::vec2 getNormalizedSize(const glm::vec2 &pixelSize);

	void logMessage(const std::string& message);
	void logWarning(const std::string& message);

private:
	void swapBuffers();
	void processInput(InputHandler *inputHandler);
	bool checkClosePressed();
	void onBeginFrame();
    uint32_t stopTimer();
	void onEndFrame();
	unsigned int getLastFrameTime();
	void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp);

friend class RenderEngine;
friend class TextureManager;
friend class SingletonsManager;
};

} // namespace

#endif