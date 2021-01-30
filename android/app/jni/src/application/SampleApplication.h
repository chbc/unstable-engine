#pragma once
#include <RenderEngine.h>
#include "ScreenManager.h"
#include "scenes/IScene.h"

using namespace sre;

class SampleApplication : public RenderEngine
{
private:
	static SampleApplication* instance;
	
public:
	SampleApplication();
	static SampleApplication* getInstance();

	void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName);
	void changeScene(IScene* newScene);

protected:
	void onInit() override;
	void onUpdate(unsigned int elapsedTime) override;
};
