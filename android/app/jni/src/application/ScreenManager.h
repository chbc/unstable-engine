#pragma once

#include "scenes/IScene.h"
#include "memory_aliases.h"

class ScreenManager
{
private:
	static ScreenManager* instance;
	SPTR<IScene> scene;

	SceneManager* sceneManager;
	GUIManager* guiManager;

public:
	static ScreenManager* getInstance();

	void onInit(SceneManager* sceneManager, GUIManager* guiManager);
	void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName);
	void changeScene(IScene* newScene);
};
