#include "RenderEngine.h"

namespace sre
{

RenderEngine::RenderEngine()
{
	this->renderManager = RenderManager::getInstance();
	this->multimediaManager = MultimediaManager::getInstance();
	this->inputHandler = nullptr;
}

void RenderEngine::run()
{
	this->multimediaManager->init();
	this->renderManager->init();
	this->sceneManager = UPTR<SceneManager>{ new SceneManager };
	this->guiManager = UPTR<GUIManager>{ new GUIManager };

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
	this->renderManager->release();
	this->multimediaManager->release();
}

void RenderEngine::processInput()
{
	if (this->inputHandler != nullptr)
		this->multimediaManager->processInput(this->inputHandler.get());
    else
		this->running = !this->multimediaManager->checkClosePressed();
}

void RenderEngine::render()
{
	this->renderManager->clearBuffer();
	this->renderManager->render();
	this->onGUI();
	this->multimediaManager->swapBuffers();
}

void RenderEngine::setEventReceiver(InputHandler *inputHandler)
{
	this->inputHandler = UPTR<InputHandler>(inputHandler);
}

void RenderEngine::quit()
{
	this->running = false;
}

} // namespace
