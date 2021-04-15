#pragma once

#include "IScene.h"
#include <GUIButtonComponent.h>

class MenuScene : public IScene
{
public:
	void onInit(SceneManager* sceneManager, GUIManager* guiManager) override;
	void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName) override;
};
