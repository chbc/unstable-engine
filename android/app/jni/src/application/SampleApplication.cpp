#include "SampleApplication.h"
#include "events/EventReceiver.h"
#include "scenes/MenuScene.h"

UPTR<IScene> scene;

SampleApplication* SampleApplication::instance = nullptr;

#ifdef __ANDROID__
SampleApplication::SampleApplication() : RenderEngine()
{
	instance = this;
	scene = UPTR<MenuScene>{ new MenuScene };
	this->setEventReceiver(new EventReceiver(this));
}
#else
SampleApplication::SampleApplication() : RenderEngine("Jogo da Memoria", 400, 623)
{
	instance = this;
	scene = UPTR<MenuScene>{ new MenuScene };
	this->setEventReceiver(new EventReceiver(this));
}
#endif

SampleApplication* SampleApplication::getInstance()
{
	return instance;
}

void SampleApplication::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	scene->onButtonPress(guiButton, entityName);
}

void SampleApplication::changeScene(IScene* newScene)
{
	scene.reset(newScene);
	this->loadScene("");
}

void SampleApplication::onInit()
{
	scene->onInit(this->sceneManager.get(), this->guiManager.get());
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{
	scene->onUpdate(elapsedTime);
}
