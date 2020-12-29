#pragma once

namespace sre
{
	class SceneManager;
}

using namespace sre;

class IScene
{
public:
	virtual ~IScene() = default;

	virtual void onInit(SceneManager* sceneManager) = 0;
	virtual void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName) = 0;
};
