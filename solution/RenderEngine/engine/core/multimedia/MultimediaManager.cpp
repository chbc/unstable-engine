#include "MultimediaManager.h"
#include <engine/core/wrappers/multimedia/SDLAPI.h>
#include <engine/core/timer/Timer.h>

namespace sre
{

IMPLEMENT_SINGLETON(MultimediaManager);

MultimediaManager::MultimediaManager()
{
	this->screenWidth = 1024.0f;
	this->screenHeight = 768.0f;

	this->aspectRatio = this->screenWidth / this->screenHeight;
}

void MultimediaManager::init()
{
	this->multimediaWrapper = UPTR<AMultimediaWrapper>{ new SDLAPI{} };
	this->multimediaWrapper->init(this->screenWidth, this->screenHeight, "SudaRA Render Engine");
	this->timer = UPTR<Timer>{ new Timer{this->multimediaWrapper.get()} };
}

void MultimediaManager::release()
{
	this->multimediaWrapper->release();
}

float MultimediaManager::getNormalizedWidth(float pixelWidth)
{
	return (pixelWidth / this->screenWidth);
}

glm::vec2 MultimediaManager::getNormalizedSize(const glm::vec2 &pixelSize)
{
	return glm::vec2(pixelSize.x / this->screenWidth, pixelSize.y / this->screenHeight);
}

void MultimediaManager::swapBuffers()
{
	this->multimediaWrapper->swapBuffers();
}

void MultimediaManager::processInput(InputHandler *inputHandler)
{
	this->multimediaWrapper->processInput(inputHandler);
}

bool MultimediaManager::checkClosePressed()
{
	return this->multimediaWrapper->checkClosePressed();
}

void MultimediaManager::onBeginFrame()
{
	this->timer->start();
}

void MultimediaManager::onEndFrame()
{
	this->timer->delay();
	this->timer->updateElapsedTime();
}

unsigned int MultimediaManager::getElapsedTime()
{
	return this->timer->getElapsedTime();
	return 0;
}

void *MultimediaManager::loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp)
{
	return this->multimediaWrapper->loadTexture(fileName, outWidth, outHeight, outBpp);
}

} // namespace