#include "SampleApplication.h"
// #include <application/events/EventReceiver.h>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	// floor //
	// RenderableNode *planeNode = this->sceneManager->addPlaneNode(5);
	/*
	Material *planeMaterial = new DiffuseMaterial("../media/woodfloor.png");
	planeNode->setMaterial(planeMaterial);
	*/

	// planeNode->setRotation(Vector(1, 0, 0), 90);

	// cube //
	/*
	this->cube = this->sceneManager->addCubeNode();
	this->cube->setPosition(Vector(0, 0.5f, 0));

	RenderableNode *cube = this->sceneManager->addCubeNode(0.5f);
	cube->setPosition(Vector(1, 0.5f, 0));
	*/
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
	// this->registerEventReceiver(new EventReceiver(this, this->sceneManager->getMainCamera()));
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{
	//this->cubeAngle += elapsedTime * 0.05f;
	//this->cube->setRotation(Vector(0, 1, 0), this->cubeAngle);
}
