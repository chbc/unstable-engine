#include "Scene.h"

#include "CameraComponent.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "ModelLoader.h"
#include "MeshComponent.h"
#include "EngineValues.h"

namespace sre
{

Scene::Scene(std::string name) : AScene(name)
{
    this->renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
}

Entity* Scene::createPerspectiveCamera(uint32_t& index, float fov, float near, float far, Entity* parent, bool isMainCamera)
{
    Entity* mainCamera = this->createEntity(index, "_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setPerspectiveProjection(fov, EngineValues::SCREEN_WIDTH / EngineValues::SCREEN_HEIGHT, near, far);

    if (isMainCamera)
        this->renderManager->setMainCamera(cameraComponent);

    return mainCamera;
}

Entity* Scene::createOrthoCamera(uint32_t& index, Entity* parent, bool isMainCamera)
{
    Entity* mainCamera = this->createEntity(index, "_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setOrthoProjection();

    if (isMainCamera)
        this->renderManager->setMainCamera(cameraComponent);

    return mainCamera;
}

Entity *Scene::createPlaneEntity(uint32_t& index, const glm::vec2& size, float tileMultiplier, const std::string& name, Entity* parent)
{
	return this->createMeshEntity(index, PrimitiveMeshFactory().createPlane(size, tileMultiplier), name, parent);
}

Entity *Scene::createCubeEntity(uint32_t& index, float size, const std::string& name, Entity* parent)
{
	return this->createMeshEntity(index, PrimitiveMeshFactory().createCube(size), name, parent);
}

Entity *Scene::createModelEntity(uint32_t& index, const std::string &fileName, const std::string& name, Entity* parent)
{
    ModelLoader modelLoader;
    Entity *rootEntity = this->createEntity(index, name, parent);
    modelLoader.load(rootEntity, fileName);

    return rootEntity;
}

// light //
DirectionalLightComponent *Scene::createDirectionalLight(uint32_t& index, const std::string& name, Entity* parent)
{
    std::string resultName = name.empty() ? "directional_light" : name;
    Entity *newEntity = this->createEntity(index, resultName, parent);

    newEntity->addComponent<DirectionalLightComponent>();
    return this->renderManager->AddDirectionalLight(newEntity);
}

PointLightComponent *Scene::createPointLight(uint32_t& index, const std::string& name, Entity* parent)
{
    std::string resultName = name.empty() ? "point_light" : name;
    Entity *newEntity = this->createEntity(index, resultName, parent);

    newEntity->addComponent<PointLightComponent>();
    return this->renderManager->AddPointLight(newEntity);
}

CameraComponent *Scene::getMainCamera()
{
	return this->renderManager->getMainCamera();
}

Entity *Scene::createMeshEntity(uint32_t& index, MeshData* objectData, const std::string& name, Entity* parent)
{
    Entity *newEntity = this->createEntity(index, name, parent);
	newEntity->addComponent<MeshComponent>(objectData);
    return newEntity;
}

void Scene::setMainCamera(CameraComponent* camera)
{
    this->renderManager->setMainCamera(camera);
}

} // namespace
