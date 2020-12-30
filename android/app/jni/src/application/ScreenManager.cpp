#include "ScreenManager.h"
#include <SceneManager.h>
#include <GUIManager.h>
#include "scenes/MenuScene.h"

ScreenManager* ScreenManager::instance = nullptr;

ScreenManager* ScreenManager::getInstance()
{
	return instance;
}

void ScreenManager::onInit(SceneManager* sceneManager, GUIManager* guiManager)
{
	instance = this;

	this->sceneManager = sceneManager;
	this->guiManager = guiManager;

	this->scene = SPTR<MenuScene>{ new MenuScene };
	this->scene->onInit(sceneManager, guiManager);
}

void ScreenManager::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	this->scene->onButtonPress(guiButton, entityName);
}

void ScreenManager::changeScene(IScene* newScene)
{
	this->sceneManager->clearEntities();
	this->guiManager->clearEntities();

	this->scene.reset(newScene);
	this->scene->onInit(this->sceneManager, this->guiManager);
}
