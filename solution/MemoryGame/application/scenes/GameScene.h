#pragma once

#include "IScene.h"
#include <GUIButtonComponent.h>

class GameScene : public IScene
{
public:
	void onInit(SceneManager* sceneManager, GUIManager* guiManager) override;
	void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName) override;

private:
	void setupCards(GUIManager* guiManager);
};
