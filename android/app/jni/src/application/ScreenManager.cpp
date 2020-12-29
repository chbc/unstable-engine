#include "ScreenManager.h"
#include <SceneManager.h>
#include "scenes/MenuScene.h"

void ScreenManager::onInit(SceneManager* sceneManager)
{
	this->scene = SPTR<MenuScene>{ new MenuScene };
	this->scene->onInit(sceneManager);
}

void ScreenManager::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	this->scene->onButtonPress(guiButton, entityName);
}
