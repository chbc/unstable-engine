#include "SampleApplication.h"
#include <application/events/EventReceiver.h>
#include <MeshComponent.h>
#include <Input.h>
#include <glm/vec3.hpp>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	this->scenesManager->createPerspectiveCamera();
	
	this->camera = this->scenesManager->getMainCamera();

	this->createLights();

	glm::vec3 position(-5.0f, 0.0f, 2.5f);
	Entity* cube;
	MeshComponent* cubeMesh;

	cube = this->scenesManager->createCubeEntity(2.0f);
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastShadow(false);

	cube = this->scenesManager->createCubeEntity(2.0f);
	position.x = 0.0f;
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("crate.png");
	cubeMesh->getMaterial()->setCastShadow(false);

	cube = this->scenesManager->createCubeEntity(2.0f);
	position.x = 5.0f;
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("crate.png");
	cubeMesh->addMaterialComponent<NormalMaterialComponent>("crate_normal.png");
	cubeMesh->getMaterial()->setCastShadow(false);

	cube = this->scenesManager->createCubeEntity(2.0f, "caixa_filha", cube);
	position = glm::vec3(0.0f, 0.0f, -2.5f);
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("crate.png");
	cubeMesh->addMaterialComponent<NormalMaterialComponent>("crate_normal.png");
	cubeMesh->addMaterialComponent<SpecularMaterialComponent>("crate_specular.png");
	cubeMesh->getMaterial()->setCastShadow(false);
}

void SampleApplication::onUpdate(unsigned int elapsedTime)
{
	this->processInput();
}

void SampleApplication::createLights()
{
	glm::vec3 p1Position(0.0f, 5.0f, 0.0f);

	Entity* lightCube = this->scenesManager->createCubeEntity(0.2f);
	lightCube->getTransform()->setPosition(p1Position);
	MeshComponent* cubeMesh = lightCube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);

	PointLightComponent* pLight1 = this->scenesManager->createPointLight("p_light_1", lightCube);
	// pLight1->getTransform()->setPosition(p1Position);
	pLight1->setColor(glm::vec3(0.5f));

	DirectionalLightComponent* dLight1 = this->scenesManager->createDirectionalLight();
	dLight1->setDirection(glm::vec3(0.0f, -0.1f, -1.0f));
	dLight1->setColor(glm::vec3(0.5f));
}

void SampleApplication::processInput()
{
	this->processKeys();
	this->processMouse();
}

void SampleApplication::processKeys()
{
	if (Input::isKeyJustPressed(KEY_ESC))
		this->quit();
	else if (Input::isKeyJustPressed(KEY_e))
		this->setEditorMode(true);
}

void SampleApplication::processMouse()
{
	if (Input::isMouseButtonJustPressed(MOUSEBUTTON_LEFT))
	{
		glm::vec3 position = this->camera->getPosition();
		position.x -= 1.0f;
		this->camera->setPosition(position);
	}
	else if (Input::isMouseButtonJustPressed(MOUSEBUTTON_RIGHT))
	{
		glm::vec3 position = this->camera->getPosition();
		position.x += 1.0f;
		this->camera->setPosition(position);
	}
}
