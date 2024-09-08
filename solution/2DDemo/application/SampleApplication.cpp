#include "SampleApplication.h"
#include "contexts/MainMenuContext.h"
#include "contexts/GameContext.h"
#include <Input.h>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	MainMenuContext::load(this->scenesManager.get());
}

void SampleApplication::onUpdate(float elapsedTime)
{
	if (Input::isKeyJustPressed(KEY_a))
	{
		std::function<void()> loadFunction = [&](void) {MainMenuContext::load(this->scenesManager.get()); };
		TEMP_loadScene(loadFunction);
	}
	if (Input::isKeyJustPressed(KEY_s))
	{
		std::function<void()> loadFunction = [&](void) {GameContext::load(this->scenesManager.get()); };
		TEMP_loadScene(loadFunction);
	}
}
