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
	camera->setPosition(glm::vec3(0.0f, 2.0f, 10.0f));

	/*
	Material *cubeMaterial = new SpecularMaterial("../media/crate.jpg");
	this->cube->setMaterial(cubeMaterial);
	*/

	// light //
	/*
	PointLight *light = this->sceneManager->addPointLight();
	light->setColor(Vector(0.7f, 0.7f, 0.7f));
	light->setPosition(Vector(1, 5, 3));
	*/

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
