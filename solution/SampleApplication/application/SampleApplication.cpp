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

	PostProcessingComponent* postProcessingComponent = camera->getEntity()->addComponent<PostProcessingComponent>();
	PostProcessingEffect* effect = postProcessingComponent->enqueueEffect(PPE::OUTLINE);

	// set EventReceiver class for input handling
	this->setEventReceiver(new EventReceiver(this, this->sceneManager->getMainCamera(), effect));

	this->createLights();

	// ### createHouse();
	// return;
	
    // cube //
	Entity* cube;
	cube = this->createCube();
    cube->getTransform()->setPosition(glm::vec3(-5.0f, 1.0f, -12.0f));


	// OUTLINE
	/* 
	cube = this->sceneManager->createCubeEntity(2.0f);
	// cube = this->sceneManager->createCubeEntity(4.0f);
	MeshComponent* cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/crate.png");
	cubeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/crate_normal.png");
	cubeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/crate_specular.png");
	// cubeMesh->addMaterialComponent<OutlineMaterialComponent>();
	// this->sceneManager->addEntity(cube, "cubo_outline");
	cube->getTransform()->setPosition(glm::vec3(5.0f, 1.0f, -12.0f));
	*/
	
	cube = this->createCube();
    cube->getTransform()->setPosition(glm::vec3(3.0f, 1.0f, 0.0f));

    this->createRoom();
	
    Entity *nanosuit = this->sceneManager->createModelEntity("../../media/nanosuit/nanosuit.obj");
    nanosuit->getTransform()->setScale(glm::vec3(0.25f, 0.25f, 0.25f));
    this->sceneManager->addEntity(nanosuit, "nanosuit");
    
    // GUI //
	/*
    Entity *guiEntity;
    guiEntity = this->guiManager->createGUIImageEntityFromAtlas("../../media/atlases/test_texture_rect", "sete");
    GUIImageComponent *guiComponent = guiEntity->getComponent<GUIImageComponent>();
    guiComponent->setUIPosition(glm::vec2(0.75f, 0.75f));
    
    this->guiManager->addEntity(guiEntity);
	*/

    /*
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
    */
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

Entity* SampleApplication::createCube()
{
	Entity* cube;
	cube = this->sceneManager->createCubeEntity(2.0f);
	// cube = this->sceneManager->createCubeEntity(4.0f);
	MeshComponent* cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/crate.png");
	cubeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/crate_normal.png");
	cubeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/crate_specular.png");

	this->sceneManager->addEntity(cube, "cube");

	return cube;
}

void SampleApplication::createLights()
{
	// light //
	/*
	DirectionalLightComponent* dLight1 = this->sceneManager->addDirectionalLight();
	dLight1->setDirection(glm::vec3(-1.0f, -0.25f, 0.0f));
	dLight1->setColor(glm::vec3(1.0f));

	DirectionalLightComponent* dLight2 = this->sceneManager->addDirectionalLight();
	dLight2->setDirection(glm::vec3(0.0f, -0.5f, -1.0f));
	dLight2->setColor(glm::vec3(0.3f));
	*/

	// nanosuit
	glm::vec3 p1Position(5.0f, 4.0f, -18.0f);
	PointLightComponent* pLight1 = this->sceneManager->addPointLight();
	pLight1->getTransform()->setPosition(p1Position);
	pLight1->setColor(glm::vec3(0.75f));

	Entity * lightCube = this->sceneManager->createCubeEntity(0.2f);
	lightCube->getTransform()->setPosition(p1Position);
	MeshComponent* cubeMesh = lightCube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastsShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);
	this->sceneManager->addEntity(lightCube, "light_cube_1");

	PointLightComponent* pLight2 = this->sceneManager->addPointLight();
	pLight2->getTransform()->setPosition(glm::vec3(0.0f, 5.0f, 5.0f));
	pLight2->setColor(glm::vec3(0.75f));
	pLight2->setRange(30.f);

	lightCube = this->sceneManager->createCubeEntity(0.2f);
	lightCube->getTransform()->setPosition(pLight2->getPosition());
	cubeMesh = lightCube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastsShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);
	this->sceneManager->addEntity(lightCube, "light_cube_2");

	/*
	PointLightComponent *pLight3 = this->sceneManager->addPointLight();
	pLight3->getTransform()->setPosition(glm::vec3(0.0f, 3.0f, -5.0f));
	pLight3->setColor(glm::vec3(0.25f, 0.25f, 0.25f));

	cube = this->sceneManager->createCubeEntity();
	cube->getTransform()->setPosition(pLight3->getPosition());
	cube->getTransform()->setScale(glm::vec3(0.25f));
	cubeMesh = cube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastsShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);
	this->sceneManager->addEntity(cube);
	*/

	// sponza
	/*
	PointLightComponent* pLight1 = this->sceneManager->addPointLight();
	pLight1->getTransform()->setPosition(glm::vec3(0.0f, 15.0f, -60.0f));
	pLight1->setColor(glm::vec3(0.5f, 0.5f, 0.15f));

	Entity* lightCube = this->sceneManager->createCubeEntity();
	lightCube->getTransform()->setPosition(pLight1->getPosition());
	lightCube->getTransform()->setScale(glm::vec3(0.2f));
	MeshComponent* cubeMesh = lightCube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastsShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);
	this->sceneManager->addEntity(lightCube);

	PointLightComponent* pLight2 = this->sceneManager->addPointLight();
	pLight2->getTransform()->setPosition(glm::vec3(-3.0f, 10.0f, -20.0f));
	pLight2->setColor(glm::vec3(0.5f, 0.15f, 0.15f));
	pLight2->setRange(40.0f);

	lightCube = this->sceneManager->createCubeEntity();
	lightCube->getTransform()->setPosition(pLight2->getPosition());
	lightCube->getTransform()->setScale(glm::vec3(0.2f));
	cubeMesh = lightCube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastsShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);
	this->sceneManager->addEntity(lightCube);

	PointLightComponent* pLight3 = this->sceneManager->addPointLight();
	pLight3->getTransform()->setPosition(glm::vec3(3.0f, 10.0f, 20.0f));
	pLight3->setColor(glm::vec3(0.5f, 0.5f, 0.5f));
	pLight3->setRange(40.0f);

	lightCube = this->sceneManager->createCubeEntity();
	lightCube->getTransform()->setPosition(pLight3->getPosition());
	lightCube->getTransform()->setScale(glm::vec3(0.2f));
	cubeMesh = lightCube->getComponent<MeshComponent>();
	cubeMesh->getMaterial()->setCastsShadow(false);
	cubeMesh->getMaterial()->setReceivesLight(false);
	this->sceneManager->addEntity(lightCube);
	*/
}

void SampleApplication::createRoom()
{
    Entity* plane;
	TransformComponent* transform;
	MeshComponent* planeMesh;

	const float TILE = 5.0f;
	
    // bottom //
    plane = this->sceneManager->createPlaneEntity(40, TILE);
    transform = plane->getTransform();
    transform->setRotation(glm::vec3(1, 0, 0), 90.0f);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/wood.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    // planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    //planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    //planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane, "floor");

	float DISTANCE = 20;
	float SIZE = 40;

    // back //
    plane = this->sceneManager->createPlaneEntity(SIZE, TILE);
	transform = plane->getTransform();
    transform->setPosition(glm::vec3(0, DISTANCE, -DISTANCE));
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane, "back_wall");


    // left //
    plane = this->sceneManager->createPlaneEntity(SIZE, TILE);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(-DISTANCE, DISTANCE, 0));
    transform->setRotation(glm::vec3(0, 1, 0), -90);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane, "left_wall");


    // right //
    plane = this->sceneManager->createPlaneEntity(SIZE, TILE);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(DISTANCE, DISTANCE, 0));
    transform->setRotation(glm::vec3(0, 1, 0), 90);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane, "right_wall");


    // front //
    plane = this->sceneManager->createPlaneEntity(SIZE, TILE);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(0, DISTANCE, DISTANCE));
    transform->setRotation(glm::vec3(1, 0, 0), -180);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane, "front_wall");


    // top //
    plane = this->sceneManager->createPlaneEntity(SIZE, TILE);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(0, DISTANCE, 0));
    transform->setRotation(glm::vec3(1, 0, 0), -90);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane, "ceiling");
}

void SampleApplication::createHouse()
{
	Entity* entity;

	// bottom //
	entity = this->sceneManager->createModelEntity("../../media/sponza/sponza.obj");
	TransformComponent* transform = entity->getTransform();
	transform->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
	transform->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), 90);

	this->sceneManager->addEntity(entity);

	// cube //
	Entity* cube;
	cube = this->createCube();
	cube->getTransform()->setPosition(glm::vec3(4.0f, 2.0f, 2.0f));

	cube = this->createCube();
	cube->getTransform()->setPosition(glm::vec3(-4.0f, 2.0f, -2.0f));

	cube = this->createCube();
	cube->getTransform()->setPosition(glm::vec3(-4.0f, 2.0f, -6.0f));
	cube = this->createCube();
	cube->getTransform()->setPosition(glm::vec3(-4.0f, 6.0f, -6.0f));
}
