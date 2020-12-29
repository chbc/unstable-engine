#include "MultimediaManager.h"
#include "SDLAPI.h"
#include "Timer.h"
#include "EngineValues.h"
#include "GUIButtonComponent.h"

#ifdef __ANDROID__
#include "SDLAndroidAPI.h"
#endif

namespace sre
{

void MultimediaManager::init()
{
#ifdef __ANDROID__
	this->multimediaWrapper = UPTR<AMultimediaWrapper>{ new SDLAndroidAPI{} };
#else
	this->multimediaWrapper = UPTR<AMultimediaWrapper>{ new SDLAPI{} };
#endif

	this->multimediaWrapper->init();
	this->timer = UPTR<Timer>{ new Timer{this->multimediaWrapper.get()} };
}

void MultimediaManager::release()
{
	this->multimediaWrapper->release();
}

float MultimediaManager::getNormalizedWidth(float pixelWidth)
{
	return (pixelWidth / EngineValues::SCREEN_WIDTH);
}

glm::vec2 MultimediaManager::getNormalizedSize(const glm::vec2 &pixelSize)
{
	return glm::vec2(pixelSize.x / EngineValues::SCREEN_WIDTH, pixelSize.y / EngineValues::SCREEN_HEIGHT);
}

void MultimediaManager::swapBuffers()
{
	this->multimediaWrapper->swapBuffers();
}

void MultimediaManager::processInput(InputHandler *inputHandler)
{
	this->multimediaWrapper->processInput(inputHandler, guiButtons);
}

bool MultimediaManager::checkClosePressed()
{
	return this->multimediaWrapper->checkClosePressed();
}

void MultimediaManager::onBeginFrame()
{
	this->timer->start();
}

uint32_t MultimediaManager::stopTimer()
{
    return this->timer->stop();
}

void MultimediaManager::onEndFrame()
{
	this->timer->delay();
}

unsigned int MultimediaManager::getLastFrameTime()
{
    return this->timer->getLastFrameTime();
}

void *MultimediaManager::loadTexture(const std::string &fileName, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp)
{
	return this->multimediaWrapper->loadTexture(fileName, outWidth, outHeight, outBpp);
}

void MultimediaManager::logMessage(const std::string& message)
{
	this->multimediaWrapper->log("MESSAGE", message);
}

void MultimediaManager::logWarning(const std::string& message)
{
	this->multimediaWrapper->log("WARNING", message);
}

void MultimediaManager::addGUIButton(GUIButtonComponent* guiButton)
{
	this->guiButtons.push_back(guiButton);
}

} // namespace
