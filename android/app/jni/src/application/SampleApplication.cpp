#include "SampleApplication.h"

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	Entity* entity = this->sceneManager->createPlaneEntity(1.0f);
	this->sceneManager->addEntity(entity);
}
