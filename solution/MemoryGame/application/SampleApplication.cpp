#include "SampleApplication.h"
#include "ScreenManager.h"

#ifdef __ANDROID__
SampleApplication::SampleApplication() : RenderEngine() { }
#else
SampleApplication::SampleApplication() : RenderEngine("Jogo da Memoria", 400, 623) { }
#endif

void SampleApplication::onInit()
{
	CameraComponent* camera = this->sceneManager->getMainCamera();
	camera->setOrthoProjection();
	
	this->screenManager.onInit(this->sceneManager.get());
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
