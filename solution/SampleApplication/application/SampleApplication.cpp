#include "SampleApplication.h"
#include <application/events/EventReceiver.h>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	// floor //
	/*
	Material *planeMaterial = new DiffuseMaterial("../media/woodfloor.png");
	planeNode->setMaterial(planeMaterial);
	*/
	Entity *plane = this->sceneManager->addPlaneEntity(5);
	TransformComponent *transform = plane->getTransform();
	transform->setRotation(glm::vec3(1, 0, 0), 90.0f);

	this->cube = this->sceneManager->addCubeEntity();
	this->cube->getTransform()->setPosition(glm::vec3(0.0f, 0.5f, 0.0f));

	CameraComponent *camera = this->sceneManager->getMainCamera();
	camera->setPosition(glm::vec3(0.0f, 1.0f, 5.0f));

	/*
	Material *cubeMaterial = new SpecularMaterial("../media/crate.jpg");
	this->cube->setMaterial(cubeMaterial);
	*/

	// light //
	DirectionalLightComponent *dLight1 = this->sceneManager->addDirectionalLight();
	dLight1->setDirection(glm::vec3(-1.0f, -1.0f, 0.0f));
	dLight1->setColor(glm::vec3(0.5f, 0.0f, 0.0f));

	DirectionalLightComponent *dLight2 = this->sceneManager->addDirectionalLight();
	dLight2->setDirection(glm::vec3(-1.0f, 0.0f, 0.0f));
	dLight2->setColor(glm::vec3(0.0f, 0.5f, 0.0f));

	// set EventReceiver class for input handling
	this->setEventReceiver(new EventReceiver(this, this->sceneManager->getMainCamera()));
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{
	/*
	//this->cubeAngle += elapsedTime * 0.05f;
	//this->cube->setRotation(Vector(0, 1, 0), this->cubeAngle);

	glm::vec3 position = this->cube->getTransform()->getPosition();
	position.x += 0.001f * elapsedTime;
	this->cube->getTransform()->setPosition(position);
	*/
}
