#include "SampleApplication.h"
#include <application/events/EventReceiver.h>
#include <engine/entities/components/meshes/MeshComponent.h>

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
	Entity *plane = this->sceneManager->addPlaneEntity(20);
	TransformComponent *transform = plane->getTransform();
	transform->setRotation(glm::vec3(1, 0, 0), 90.0f);
	Material *material = plane->getComponent<MeshComponent>()->getMaterial();
	DiffuseMaterialComponent *diffuseMaterial = material->addComponent<DiffuseMaterialComponent>
	(
		"../../media/testTexture.png"
	);

	this->cube = this->sceneManager->addCubeEntity();
	this->cube->getTransform()->setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
	material = cube->getComponent<MeshComponent>()->getMaterial();
	ColorMaterialComponent *colorMaterial = material->getComponent<ColorMaterialComponent>();
	colorMaterial->setColor(glm::vec4(0.2f, 0.2f, 1.0f, 1.0f));


	CameraComponent *camera = this->sceneManager->getMainCamera();
	camera->setPosition(glm::vec3(0.0f, 5.0f, 10.0f));

	/*
	Material *cubeMaterial = new SpecularMaterial("../media/crate.jpg");
	this->cube->setMaterial(cubeMaterial);
	*/

	// light //
	/*
	DirectionalLightComponent *dLight1 = this->sceneManager->addDirectionalLight();
	dLight1->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
	dLight1->setColor(glm::vec3(0.0f, 0.5f, 0.0f));
	*/

	/*
	DirectionalLightComponent *dLight2 = this->sceneManager->addDirectionalLight();
	dLight2->setDirection(glm::vec3(1.0f, 0.0f, -1.0f));
	dLight2->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	*/

	PointLightComponent *pLight1 = this->sceneManager->addPointLight();
	pLight1->getTransform()->setPosition(glm::vec3(5.0f, 5.0f, 0.0f));
	pLight1->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

	PointLightComponent *pLight2 = this->sceneManager->addPointLight();
	pLight2->getTransform()->setPosition(glm::vec3(-5.0f, 5.0f, 0.0f));
	pLight2->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

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
