#include "MultimediaManager.h"
#include <engine/systems/wrappers/multimedia/SDLAPI.h>
#include <engine/systems/timer/Timer.h>

namespace sre
{

IMPLEMENT_SINGLETON(MultimediaManager);

MultimediaManager::MultimediaManager()
{
}

void MultimediaManager::init()
{
	this->multimediaWrapper = UPTR<AMultimediaWrapper>{ new SDLAPI{} };
	this->multimediaWrapper->init(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->timer = UPTR<Timer>{ new Timer{this->multimediaWrapper.get()} };
}

void MultimediaManager::release()
{
	this->multimediaWrapper->release();
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
