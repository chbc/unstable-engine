#include "MultimediaManager.h"
#include <engine/systems/wrappers/multimedia/AMultimediaWrapper.h>
#include <engine/systems/timer/Timer.h>

namespace sre
{

IMPLEMENT_SINGLETON(MultimediaManager);

MultimediaManager::MultimediaManager()
{
}

bool MultimediaManager::init()
{
	this->multimediaWrapper = AMultimediaWrapper::getInstance();
	this->multimediaWrapper->init(SCREEN_WIDTH, SCREEN_HEIGHT);

	this->timer = std::unique_ptr<Timer>{ new Timer() };

	return true;
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
}

} // namespace
