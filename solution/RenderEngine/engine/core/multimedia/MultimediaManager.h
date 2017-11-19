#ifndef _MULTIMEDIA_MANAGER_H_
#define _MULTIMEDIA_MANAGER_H_

#include <glm/vec2.hpp>
#include <engine/utils/memory_aliases.h>
#include <engine/core/singletonsManager/ISingleton.h>

namespace sre
{

class AMultimediaWrapper;
class InputHandler;
class Timer;

/*!
	Class for window management
*/
class MultimediaManager : public ISingleton
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

private:
	void swapBuffers();
	void processInput(InputHandler *inputHandler);
	bool checkClosePressed();
	void onBeginFrame();
	void onEndFrame();
	unsigned int getElapsedTime();
	void *loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp);

friend class RenderEngine;
friend class TextureManager;
friend class SingletonsManager;
};

} // namespace

#endif
