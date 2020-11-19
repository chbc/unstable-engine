#include "SampleApplication.h"
#include <application/events/EventReceiver.h>
#include <MeshComponent.h>
#include <PostProcessingComponent.h>
#include <sstream>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	CameraComponent* camera = this->sceneManager->getMainCamera();

	// set EventReceiver class for input handling
	this->setEventReceiver(new EventReceiver(this, this->sceneManager->getMainCamera()));

	this->createLights();

	glm::vec3 position(-5.0f, 0.0f, 2.5f);
	Entity* cube;
	cube = this->sceneManager->createCubeEntity(2.0f);
	cube->getTransform()->setPosition(position);

	this->sceneManager->addEntity(cube);

	cube = this->sceneManager->createCubeEntity(2.0f);
	position.x = 0.0f;
	cube->getTransform()->setPosition(position);
	MeshComponent* cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/crate.png");
	cubeMesh->getMaterial()->setCastShadow(false);

	this->sceneManager->addEntity(cube);

	cube = this->sceneManager->createCubeEntity(2.0f);
	position.x = 5.0f;
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/crate.png");
	cubeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/crate_normal.png");
	cubeMesh->getMaterial()->setCastShadow(false);

	this->sceneManager->addEntity(cube);
	
	cube = this->sceneManager->createCubeEntity(2.0f);
	position = glm::vec3(0.0f, 0.0f, -2.5f);
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/crate.png");
	cubeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/crate_normal.png");
	cubeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/crate_specular.png");
	cubeMesh->getMaterial()->setCastShadow(false);

	this->sceneManager->addEntity(cube);
}

void SampleApplication::createLights()
{
	glm::vec3 p1Position(0.0f, 5.0f, 0.0f);
	PointLightComponent* pLight1 = this->sceneManager->addPointLight();
	pLight1->getTransform()->setPosition(p1Position);
	pLight1->setColor(glm::vec3(0.5f));

	Entity* lightCube = this->sceneManager->createCubeEntity(0.2f);
	lightCube->getTransform()->setPosition(p1Position);
	MeshComponent* cubeMesh = lightCube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);
	this->sceneManager->addEntity(lightCube);

	DirectionalLightComponent* dLight1 = this->sceneManager->addDirectionalLight();
	dLight1->setDirection(glm::vec3(0.0f, -0.1f, -1.0f));
	dLight1->setColor(glm::vec3(0.5f));
}
