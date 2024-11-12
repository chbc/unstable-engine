#include "Scene.h"

#include "CameraComponent.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "ModelLoader.h"
#include "EngineValues.h"
#include "MeshComponent.h"

namespace sre
{

Scene::Scene(std::string name) : AScene(name)
{
    this->renderManager = SingletonsManager::getInstance()->get<RenderManager>();
}

Entity* Scene::createPerspectiveCamera(float fov, float near, float far, Entity* parent, bool isMainCamera)
{
    Entity* mainCamera = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setPerspectiveProjection(fov, EngineValues::SCREEN_WIDTH / EngineValues::SCREEN_HEIGHT, near, far);

    return mainCamera;
}

Entity* Scene::createOrthoCamera(Entity* parent, bool isMainCamera)
{
    Entity* mainCamera = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setOrthoProjection();

    return mainCamera;
}

void Scene::createMeshEntity(const char* name, const char* fileName)
{
    Entity* entity = this->createEntity(name);
    MeshComponent* meshComponent = entity->addComponent<MeshComponent>();
    meshComponent->load(fileName);
}

Entity *Scene::createModelEntity(const std::string &fileName, const std::string& name, Entity* parent)
{
    ModelLoader modelLoader;
    Entity *rootEntity = this->createEntity(name, parent);
    modelLoader.load(rootEntity, fileName);

    return rootEntity;
}

// light //
DirectionalLightComponent *Scene::createDirectionalLight(const std::string& name, Entity* parent)
{
    std::string resultName = name.empty() ? "directional_light" : name;
    Entity *newEntity = this->createEntity(resultName, parent);

    return newEntity->addComponent<DirectionalLightComponent>();
}

PointLightComponent *Scene::createPointLight(const std::string& name, Entity* parent)
{
    std::string resultName = name.empty() ? "point_light" : name;
    Entity *newEntity = this->createEntity(resultName, parent);

    return newEntity->addComponent<PointLightComponent>();
}

} // namespace
