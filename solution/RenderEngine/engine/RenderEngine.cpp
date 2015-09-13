#include "RenderEngine.h"
#include <iostream>
#include <exception>

RenderEngine::RenderEngine()
{
	this->renderManager = RenderManager::getInstance();
	this->multimediaManager = MultimediaManager::getInstance();
	this->inputHandler = NULL;
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
		this->timer.start();

		this->processInput();
		this->onUpdate(timer.getElapsedTime());
		this->render();

		this->timer.delay();
		this->timer.updateElapsedTime();
	}

	this->release();
}

void RenderEngine::release()
{
	this->sceneManager->release();
	delete this->sceneManager;

	this->renderManager->release();
	delete this->renderManager;

	if (this->inputHandler != NULL)
		delete this->inputHandler;

	this->multimediaManager->release();
	delete this->multimediaManager;
}

void RenderEngine::processInput()
{
	if (this->inputHandler != NULL)
		this->inputHandler->process();
    else
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if( e.type == SDL_QUIT )
                this->running = false;
        }
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
