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

	this->entity = this->sceneManager->createPlaneEntity();
	MeshComponent* mesh = this->entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("../../media/test_texture.png");

	Entity* child = this->sceneManager->createPlaneEntity(0.5f);
	child->getTransform()->setLocalPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	this->entity->addChild(child);

	this->sceneManager->addEntity(this->entity);
	
	this->setEventReceiver(new EventReceiver(this, camera));
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{
	glm::vec3 position = this->entity->getTransform()->getPosition();
	position.y += static_cast<float>(elapsedTime) * 0.001f;
	this->entity->getTransform()->setPosition(position);
}
