#include "Scene.h"

#include "CameraComponent.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "EngineValues.h"
#include "MeshComponent.h"

namespace sre
{

Scene::Scene(std::string arg_name, std::string arg_filePath) : AScene(arg_name, arg_filePath) { }

Entity* Scene::createPerspectiveCamera(float fov, float near, float far, Entity* parent, bool isMainCamera)
{
    Entity* mainCamera = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setPerspectiveProjection(fov, EngineValues::ASPECT_RATIO, near, far);

    return mainCamera;
}

Entity* Scene::createOrthoCamera(Entity* parent, bool isMainCamera)
{
    Entity* mainCamera = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setOrthoProjection();

    return mainCamera;
}

Entity* Scene::createMeshEntity(const char* entityName, const char* filePath)
{
    Entity* entity = this->createEntity(entityName);
    MeshComponent* meshComponent = entity->addComponent<MeshComponent>();
    meshComponent->load(filePath);
    this->renderManager->addEntity(entity);

    return entity;
}

// light //
DirectionalLightComponent *Scene::createDirectionalLight(const std::string& entityName, Entity* parent)
{
    std::string resultName = entityName.empty() ? "directional_light" : entityName;
    Entity *newEntity = this->createEntity(resultName, parent);

    return newEntity->addComponent<DirectionalLightComponent>();
}

PointLightComponent *Scene::createPointLight(const std::string& entityName, Entity* parent)
{
    std::string resultName = entityName.empty() ? "point_light" : entityName;
    Entity *newEntity = this->createEntity(resultName, parent);

    return newEntity->addComponent<PointLightComponent>();
}

} // namespace
