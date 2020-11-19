#include "SampleApplication.h"
#include "application/events/EventReceiver.h"
#include <MeshComponent.h>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	CameraComponent* camera = this->sceneManager->getMainCamera();
	camera->setOrthoProjection(10.0f, 10.0f);

	Entity* entity = this->sceneManager->createPlaneEntity();
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->getMaterial()->setCastShadow(false);
	mesh->addMaterialComponent<SpriteMaterialComponent>("../../media/test_texture.png");

	this->sceneManager->addEntity(entity);
	
	this->setEventReceiver(new EventReceiver(this, camera));
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{

}
