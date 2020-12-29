#pragma once

#include "scenes/IScene.h"
#include "memory_aliases.h"

class ScreenManager
{
private:
	SPTR<IScene> scene;

public:
	void onInit(SceneManager* sceneManager);
	void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName);
};
