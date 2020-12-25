#include "SampleApplication.h"
#include "application/events/EventReceiver.h"
#include <MeshComponent.h>

#ifdef __ANDROID__
SampleApplication::SampleApplication() : RenderEngine() { }
#else
SampleApplication::SampleApplication() : RenderEngine("Jogo da Memoria", 400, 623) { }
#endif

void SampleApplication::onInit()
{
	CameraComponent* camera = this->sceneManager->getMainCamera();
	camera->setOrthoProjection();

	Entity* entity = this->sceneManager->createPlaneEntity(100.0f);
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/card_1.png");
	mesh->getMaterial()->setReceivesLight(false);

	Entity* child = this->sceneManager->createPlaneEntity(200.0f);
	mesh = child->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/base_card.png");
	mesh->getMaterial()->setReceivesLight(false);

	glm::vec3 position = entity->getTransform()->getPosition();
	child->getTransform()->setPosition(glm::vec3(0.0f, -(EngineValues::SCREEN_HEIGHT * 0.5f) + 50.0f, 0.0f));

	this->sceneManager->addEntity(entity, "moving_image");
	this->sceneManager->addEntity(child);
	
	this->setEventReceiver(new EventReceiver(this, child));

	this->direction = glm::vec2(1.0f, 1.0f);
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{
	/* XXX
	const glm::vec2 BORDERS(this->halfScreenWidth, this->halfScreenHeight);

	Entity* entity = this->sceneManager->getEntity("moving_image");

	glm::vec3 position = entity->getTransform()->getPosition();
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

	entity->getTransform()->setPosition(position);
	*/
}
