#include "SampleApplication.h"
#include <application/events/EventReceiver.h>
#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <sstream>

SampleApplication::SampleApplication() : RenderEngine()
{
}

void SampleApplication::onInit()
{
    // cube //
    Entity *cube;
    cube = this->sceneManager->createCubeEntity();
    cube->getTransform()->setPosition(glm::vec3(0.0f, 0.5f, 2.0f));
    MeshComponent *cubeMesh = cube->getComponent<MeshComponent>();
    cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/crate.png");
    
    this->sceneManager->addEntity(cube);

    cube = this->sceneManager->createCubeEntity();
    cube->getTransform()->setPosition(glm::vec3(3.0f, 4.0f, 0.0f));
    cubeMesh = cube->getComponent<MeshComponent>();
    cubeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/crate.png");

    this->sceneManager->addEntity(cube);

    this->createRoom();
    /*
    Entity *nanosuit = this->sceneManager->createModelEntity("../../media/nanosuit/nanosuit.obj");
    nanosuit->getTransform()->setScale(glm::vec3(0.25f, 0.25f, 0.25f));
    this->sceneManager->addEntity(nanosuit);
    */
    
    // light //
    DirectionalLightComponent *dLight1 = this->sceneManager->addDirectionalLight();
    dLight1->setDirection(glm::vec3(0.0f, -0.25f, -1.0f));
    dLight1->setColor(glm::vec3(1.0f));
    
/*
    DirectionalLightComponent *dLight2 = this->sceneManager->addDirectionalLight();
    dLight2->setDirection(glm::vec3(0.0f, -1.0f, -1.0f));
    dLight2->setColor(glm::vec3(0.75f, 0.75f, 0.75f));
    */

    /*
    PointLightComponent *pLight1 = this->sceneManager->addPointLight();
    pLight1->getTransform()->setPosition(glm::vec3(3.0f, 2.0f, 3.0f));
    pLight1->setColor(glm::vec3(1.0f));

    Entity *lightCube = this->sceneManager->createCubeEntity();
    lightCube->getTransform()->setPosition(pLight1->getPosition());
    lightCube->getTransform()->setScale(glm::vec3(0.2f));
    cubeMesh = lightCube->getComponent<MeshComponent>();
    cubeMesh->getMaterial()->setCastsShadow(false);
    cubeMesh->getMaterial()->setReceivesLight(false);
    this->sceneManager->addEntity(lightCube);

    PointLightComponent *pLight2 = this->sceneManager->addPointLight();
    pLight2->getTransform()->setPosition(glm::vec3(-3.0f, 3.0f, 5.0f));
    pLight2->setColor(glm::vec3(0.5f, 0.5f, 0.5f));

    lightCube = this->sceneManager->createCubeEntity();
    lightCube->getTransform()->setPosition(pLight2->getPosition());
    lightCube->getTransform()->setScale(glm::vec3(0.2f));
    cubeMesh = lightCube->getComponent<MeshComponent>();
    cubeMesh->getMaterial()->setCastsShadow(false);
    cubeMesh->getMaterial()->setReceivesLight(false);
    this->sceneManager->addEntity(lightCube);
    */

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
    
    // GUI //
    /*
    Entity *guiEntity;
    guiEntity = this->guiManager->createGUIImageEntityFromAtlas("../../media/atlases/test_texture_rect", "sete");
    GUIImageComponent *guiComponent = guiEntity->getComponent<GUIImageComponent>();
    guiComponent->setUIPosition(glm::vec2(0.5f, 0.5f));
    
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

void SampleApplication::createRoom()
{
    Entity *plane;

    // bottom //
    plane = this->sceneManager->createPlaneEntity(20);
    TransformComponent *transform = plane->getTransform();
    transform->setRotation(glm::vec3(1, 0, 0), 90.0f);
    MeshComponent *planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/wood.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    // planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    //planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    //planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane);

    // back //
    plane = this->sceneManager->createPlaneEntity(20);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(0, 0, -10));
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane);


    // left //
    plane = this->sceneManager->createPlaneEntity(20);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(-10, 0, 0));
    transform->setRotation(glm::vec3(0, 1, 0), -90);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane);


    // right //
    plane = this->sceneManager->createPlaneEntity(20);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(10, 0, 0));
    transform->setRotation(glm::vec3(0, 1, 0), 90);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane);


    // front //
    plane = this->sceneManager->createPlaneEntity(20);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(0, 0, 10));
    transform->setRotation(glm::vec3(1, 0, 0), -180);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane);


    // top //
    plane = this->sceneManager->createPlaneEntity(20);
    transform = plane->getTransform();
    transform->setPosition(glm::vec3(0, 10, 0));
    transform->setRotation(glm::vec3(1, 0, 0), -90);
    planeMesh = plane->getComponent<MeshComponent>();
    planeMesh->addMaterialComponent<DiffuseMaterialComponent>("../../media/floor2_diffuse.png");
    planeMesh->getMaterial()->setCastsShadow(false);
    planeMesh->addMaterialComponent<NormalMaterialComponent>("../../media/floor2_normal.png");
    planeMesh->addMaterialComponent<SpecularMaterialComponent>("../../media/floor2_specular.png");
    planeMesh->addMaterialComponent<AmbientOcclusionMaterialComponent>("../../media/floor2_ao.png");

    this->sceneManager->addEntity(plane);
}
