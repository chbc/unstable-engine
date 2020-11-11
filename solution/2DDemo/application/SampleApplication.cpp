#include "SampleApplication.h"
#include <MeshComponent.h>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	CameraComponent* camera = this->sceneManager->getMainCamera();

	Entity* entity = this->sceneManager->createPlaneEntity();
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->getMaterial()->setCastShadow(false);

	this->sceneManager->addEntity(entity);
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{

}
