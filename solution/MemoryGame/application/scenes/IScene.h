#pragma once

#include <string>

namespace sre
{
	class SceneManager;
	class GUIManager;
	class GUIButtonComponent;
}

using namespace sre;

class IScene
{
public:
	virtual ~IScene() = default;

	virtual void onInit(SceneManager* sceneManager, GUIManager* guiManager) = 0;
	virtual void onUpdate(unsigned int elapsedTime) { }
	virtual void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName) = 0;
};
