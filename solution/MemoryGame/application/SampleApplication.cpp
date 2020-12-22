#include "SampleApplication.h"
#include "application/events/EventReceiver.h"
#include <MeshComponent.h>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	CameraComponent* camera = this->sceneManager->getMainCamera();
	camera->setOrthoProjection(800.0f, 1247.0f);

	this->entity = this->sceneManager->createPlaneEntity(100.0f);
	MeshComponent* mesh = this->entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("media/test_texture.png");
	mesh->getMaterial()->setReceivesLight(false);

	Entity* child = this->sceneManager->createPlaneEntity(200.0f);
	mesh = child->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("media/test_texture.png");
	mesh->getMaterial()->setReceivesLight(false);

	child->getTransform()->setPosition(glm::vec3(0.0f, -500.0f, 0.0f));

	this->sceneManager->addEntity(this->entity);
	this->sceneManager->addEntity(child);
	
	this->setEventReceiver(new EventReceiver(this, child));

	this->direction = glm::vec2(1.0f, 1.0f);
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{
	const glm::vec2 BORDERS(400.0f, 623.0f);

	glm::vec3 position = this->entity->getTransform()->getPosition();
	float delta = static_cast<float>(elapsedTime);
	const float SPEED = 0.1f;
	position.x += this->direction.x * (delta * SPEED);
	position.y += this->direction.y * (delta * SPEED);

	if (position.x < -BORDERS.x)
		this->direction.x = 1.0f;
	else if (position.x > BORDERS.x)
		this->direction.x = -1.0f;

	if (position.y < -BORDERS.y)
		this->direction.y = 1.0f;
	else if (position.y > BORDERS.y)
		this->direction.y = -1.0f;

	this->entity->getTransform()->setPosition(position);
}
