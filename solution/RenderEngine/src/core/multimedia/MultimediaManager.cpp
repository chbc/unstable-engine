#include "MultimediaManager.h"
#include "SDLAPI.h"
#include "Timer.h"
#include "EngineValues.h"
#include "GUIButtonComponent.h"
#include "Entity.h"
#include "CollectionsUtils.h"
#include "Input.h"

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

void MultimediaManager::setExecutionMode(EExecutionMode::Type mode)
{
	this->multimediaWrapper->setExecutionMode(mode);
}

void MultimediaManager::processInput()
{
	this->multimediaWrapper->processInput(this->guiButtons);
}

bool MultimediaManager::checkClosePressed()
{
	return Input::isCloseButtonDown();
}

void MultimediaManager::onFrameBegin()
{
	this->multimediaWrapper->onFrameBegin();
	this->timer->start();
}

uint32_t MultimediaManager::stopTimer()
{
    return this->timer->stop();
}

void MultimediaManager::delay()
{
	this->timer->delay();
}

uint32_t MultimediaManager::getLastFrameTime()
{
    return this->timer->getLastFrameTime();
}

void *MultimediaManager::loadTexture(const std::string& filePath, uint32_t *outWidth, uint32_t *outHeight, uint8_t *outBpp)
{
	return this->multimediaWrapper->loadTexture(filePath, outWidth, outHeight, outBpp);
}

void MultimediaManager::logMessage(const std::string& message) const
{
	this->multimediaWrapper->log("MESSAGE", message);
}

void MultimediaManager::logWarning(const std::string& message) const
{
	this->multimediaWrapper->log("WARNING", message);
}

void MultimediaManager::showMessageBox(const std::string& title, const std::string& message)
{
	SDLAPI::showMessageBox(title, message);
}

void MultimediaManager::showErrorMessageBox(const std::string& title, const std::string& message)
{
	SDLAPI::showErrorMessageBox(title, message);
}

void MultimediaManager::openFileDialog(const std::string& title, const char* filter, std::string& outFileName)
{
	SDLAPI::openFileDialog(title, filter, outFileName);
}

void MultimediaManager::saveFileDialog(const std::string& title, const char* filter, std::string& outFileName)
{
	SDLAPI::saveFileDialog(title, filter, outFileName);
}

void MultimediaManager::addGUIButton(GUIButtonComponent* guiButton)
{
	this->guiButtons.push_back(guiButton);
}

void MultimediaManager::removeDestroyedEntities()
{
	CollectionsUtils::removeIfEntityIsDestroyed(this->guiButtons);
}

void MultimediaManager::cleanUp()
{
	this->guiButtons.clear();
}

} // namespace
