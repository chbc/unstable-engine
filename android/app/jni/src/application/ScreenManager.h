/* XXX
#pragma once

#include "scenes/IScene.h"
#include "memory_aliases.h"

class ScreenManager
{
private:
	SPTR<IScene> scene;

	SceneManager* sceneManager;
	GUIManager* guiManager;

public:
	void onInit(SceneManager* sceneManager, GUIManager* guiManager);
	void onUpdate(unsigned int elapsedTime);
	void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName);
	void changeScene(IScene* newScene);
};
*/