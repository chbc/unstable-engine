#include "SampleApplication.h"
#include <application/events/EventReceiver.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/gui/GUIImageComponent.h>
#include <sstream>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
	// cube //
	/*
	this->cube = this->sceneManager->createCubeEntity();
	this->cube->getTransform()->setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
	MeshComponent *cubeMesh = this->cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");

	this->sceneManager->addEntity(this->cube);
	*/

	// floor //
	/* 
	Entity *plane = this->sceneManager->createPlaneEntity(10);
	TransformComponent *transform = plane->getTransform();
	transform->setRotation(glm::vec3(1, 0, 0), 90.0f);
	MeshComponent *planeMesh = plane->getComponent<MeshComponent>();
	planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
	planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
	planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
	planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

	this->sceneManager->addEntity(plane);
	*/

	/*
	Entity *nanosuit = this->sceneManager->createModelEntity("../../media/nanosuit/nanosuit.obj");
	nanosuit->getTransform()->setScale(glm::vec3(0.25f, 0.25f, 0.25f));
	this->sceneManager->addEntity(nanosuit);

	// light //
	DirectionalLightComponent *dLight1 = this->sceneManager->addDirectionalLight();
	dLight1->setDirection(glm::vec3(0.0f, -1.0f, 1.0f));
	dLight1->setColor(glm::vec3(0.3f, 0.3f, 0.3f));
	*/

	/*
	DirectionalLightComponent *dLight2 = this->sceneManager->addDirectionalLight();
	dLight2->setDirection(glm::vec3(1.0f, 0.0f, -1.0f));
	dLight2->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	*/

	/* 
	PointLightComponent *pLight1 = this->sceneManager->addPointLight();
	pLight1->getTransform()->setPosition(glm::vec3(0.0f, 5.0f, 3.0f));
	pLight1->setColor(glm::vec3(0.5f, 0.5f, 0.5f));
	*/

	/*
	PointLightComponent *pLight2 = this->sceneManager->addPointLight();
	pLight2->getTransform()->setPosition(glm::vec3(-2.0f, 2.0f, 0.0f));
	pLight2->setColor(glm::vec3(0.5f, 0.25f, 0.0f));
	*/	

	// set EventReceiver class for input handling
	this->setEventReceiver(new EventReceiver(this, this->sceneManager->getMainCamera()));

	// GUI //
	Entity *guiEntity;
	/* 
	guiEntity = this->guiManager->createGUIImageEntityFromAtlas("../../media/atlases/test_texture_rect", "sete");
	GUIImageComponent *guiComponent = guiEntity->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.5f, 0.5f));

	this->guiManager->addEntity(guiEntity);
	*/

    std::stringstream ss;
    for (int i = 0; i < 10; i++)
    {
        guiEntity = this->guiManager->createGUITextEntity("../../media/fonts/verdana");
        GUITextComponent *textComponent = guiEntity->getComponent<GUITextComponent>();
        textComponent->setUIPosition(glm::vec2(0.25f, 0.1f + i * 0.05f));
        ss << "Texto " << i;
        textComponent->setText(ss.str());
        this->guiManager->addEntity(guiEntity);

        ss.str( std::string() );
        ss.clear();
    }
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
