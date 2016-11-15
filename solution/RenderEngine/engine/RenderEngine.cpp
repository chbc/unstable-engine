#include "RenderEngine.h"

/* ###
#include <iostream>
#include <exception>
*/

namespace sre
{

RenderEngine::RenderEngine()
{
	this->renderManager = RenderManager::getInstance();
	this->multimediaManager = MultimediaManager::getInstance();
	this->inputHandler = nullptr;

	// ### this->sceneManager = SceneManager::getInstance();
}

void RenderEngine::run()
{
	this->multimediaManager->init();
	this->renderManager->init();
	// ### this->sceneManager->init();

	this->onInit();

	this->running = true;
	while(this->running)
	{
		this->multimediaManager->onBeginFrame();

		this->processInput();
		this->onUpdate(this->multimediaManager->getElapsedTime());
		this->render();

		this->multimediaManager->onEndFrame();
	}

	this->release();
}

void RenderEngine::release()
{
	/* ###
	this->sceneManager->release();
	delete this->sceneManager;
	*/

	this->renderManager->release();
	this->multimediaManager->release();
}

void RenderEngine::processInput()
{
	if (this->inputHandler != NULL)
		this->multimediaManager->processInput(this->inputHandler.get());
    else
		this->running = !this->multimediaManager->checkClosePressed();
}

void RenderEngine::render()
{
	this->renderManager->clearBuffer();
	/* ###
	this->sceneManager->render();
	*/
	RenderManager::DEBUG_drawTriangle();

	this->multimediaManager->swapBuffers();
}

void RenderEngine::registerEventReceiver(InputHandler *inputHandler)
{
	this->inputHandler = SPTR<InputHandler>(inputHandler);
}

void RenderEngine::quit()
{
	this->running = false;
}

} // namespace
