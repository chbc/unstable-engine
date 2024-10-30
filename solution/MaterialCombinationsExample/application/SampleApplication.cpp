#include "SampleApplication.h"
#include <MeshComponent.h>
#include <Input.h>
#include <glm/vec3.hpp>

SampleApplication::SampleApplication() : RenderEngine(), camera(nullptr)
{
}

void SampleApplication::onInit()
{
	/*
	PointLightComponent* pLight1 = this->scenesManager->createPointLight("p_light_1");
	pLight1->getTransform()->setPosition(glm::vec3{0.0f, 5.0f, 0.0f});
	pLight1->setColor(glm::vec3(0.5f));
	*/

	/*
	Entity* cameraEntity = this->scenesManager->createPerspectiveCamera(90.0f);
	this->camera = cameraEntity->getComponent<CameraComponent>();
	this->camera->setPosition({ 0.0f, 5.0f, 5.0f });

	// this->createLights();
	glm::vec3 position(-5.0f, 0.0f, -2.5f);
	Entity* cube;
	MeshComponent* cubeMesh;

	cube = this->scenesManager->createCubeEntity(2.0f);
	cube->getTransform()->setPosition(position);
	*/
	/*
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setReceivesLight(true);
	cubeMesh->getMaterial()->setCastShadow(false);

	cube = this->scenesManager->createCubeEntity(2.0f);
	position.x = 0.0f;
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("crate.png");
	cubeMesh->getMaterial()->setReceivesLight(true);
	cubeMesh->getMaterial()->setCastShadow(false);

	cube = this->scenesManager->createCubeEntity(2.0f);
	position.x = 5.0f;
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("crate.png");
	cubeMesh->addMaterialComponent<NormalMaterialComponent>("crate_normal.png");
	cubeMesh->getMaterial()->setReceivesLight(true);
	cubeMesh->getMaterial()->setCastShadow(false);

	cube = this->scenesManager->createCubeEntity(2.0f, "caixa_filha", cube);
	position = glm::vec3(0.0f, 0.0f, -5.0f);
	cube->getTransform()->setPosition(position);
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("crate.png");
	cubeMesh->addMaterialComponent<NormalMaterialComponent>("crate_normal.png");
	cubeMesh->addMaterialComponent<SpecularMaterialComponent>("crate_specular.png");
	cubeMesh->getMaterial()->setReceivesLight(true);
	cubeMesh->getMaterial()->setCastShadow(false);
	*/
}

void SampleApplication::onUpdate(float elapsedTime)
{
	this->processMouse();
}

void SampleApplication::createLights()
{
	/*
	glm::vec3 p1Position(0.0f, 5.0f, 0.0f);

	Entity* lightCube = this->scenesManager->createCubeEntity(0.2f);
	lightCube->getTransform()->setPosition(p1Position);
	MeshComponent* cubeMesh = lightCube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);

	PointLightComponent* pLight1 = this->scenesManager->createPointLight("p_light_1", lightCube);
	pLight1->getTransform()->setPosition(p1Position);
	pLight1->setColor(glm::vec3(0.5f));
	*/
}

void SampleApplication::processMouse()
{
	/*
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
	*/
}
