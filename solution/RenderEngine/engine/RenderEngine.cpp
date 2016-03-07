#include "RenderEngine.h"
#include <iostream>
#include <exception>

namespace sre
{

RenderEngine::RenderEngine()
{
	this->renderManager = RenderManager::getInstance();
	this->multimediaManager = MultimediaManager::getInstance();
	this->inputHandler = nullptr;
	this->sceneManager = SceneManager::getInstance();
}

void RenderEngine::run()
{
	if (!this->multimediaManager->init())
		std::cout << "Error: MultimediaManager - init";
	if (!this->renderManager->init())
		std::cout << "Error: RenderManager - init";
	if (!this->sceneManager->init())
		std::cout << "Error: SceneManager - init";


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
	this->sceneManager->release();
	delete this->sceneManager;

	this->renderManager->release();
	delete this->renderManager;

	if (this->inputHandler != nullptr)
		delete this->inputHandler;

	this->multimediaManager->release();
	delete this->multimediaManager;
}

void RenderEngine::processInput()
{
	if (this->inputHandler != NULL)
		this->multimediaManager->processInput(this->inputHandler);
    else
    {
		this->running = !this->multimediaManager->checkClosePressed();
    }
}

void RenderEngine::render()
{
	this->renderManager->clearBuffer();
	this->sceneManager->render();
	this->multimediaManager->swapBuffers();
}

void RenderEngine::registerEventReceiver(InputHandler *inputHandler)
{
	this->inputHandler = inputHandler;
}

void RenderEngine::quit()
{
	this->running = false;
}

} // namespace
