#include "SampleApplication.h"
#include "contexts/MainMenuContext.h"

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	MainMenuContext::load(this->scenesManager.get());
}
