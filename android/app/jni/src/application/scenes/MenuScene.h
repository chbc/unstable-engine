#pragma once

#include "IScene.h"
#include <GUIButtonComponent.h>

class MenuScene : public IScene
{
public:
	void onInit(SceneManager* sceneManager) override;
	void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName) override;
};
