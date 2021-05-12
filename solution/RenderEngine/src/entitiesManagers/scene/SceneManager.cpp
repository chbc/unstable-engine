#include "SceneManager.h"

#include "CameraComponent.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "ModelLoader.h"
#include "MeshComponent.h"
#include "EngineValues.h"

namespace sre
{

SceneManager::SceneManager() : AEntityManager()
{
}

Entity* SceneManager::createPerspectiveCamera(float fov, float near, float far, Entity* parent)
{
    Entity* mainCamera = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setPerspectiveProjection(fov, EngineValues::SCREEN_WIDTH / EngineValues::SCREEN_HEIGHT, near, far);

    SingletonsManager::getInstance()->resolve<RenderManager>()->setMainCamera(cameraComponent);

    return mainCamera;
}

Entity* SceneManager::createOrthoCamera(Entity* parent)
{
    Entity* mainCamera = this->createEntity("_main_camera", parent);
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setOrthoProjection();

    SingletonsManager::getInstance()->resolve<RenderManager>()->setMainCamera(cameraComponent);

    return mainCamera;
}

Entity *SceneManager::createPlaneEntity(const glm::vec2& size, float tileMultiplier, const std::string& name, Entity* parent)
{
	return this->createMeshEntity(PrimitiveMeshFactory().createPlane(size, tileMultiplier), name, parent);
}

Entity *SceneManager::createCubeEntity(float size, const std::string& name, Entity* parent)
{
	return this->createMeshEntity(PrimitiveMeshFactory().createCube(size), name, parent);
}

Entity *SceneManager::createModelEntity(const std::string &fileName, const std::string& name, Entity* parent)
{
    ModelLoader modelLoader;
    Entity *rootEntity = this->createEntity(name, parent);
    modelLoader.load(rootEntity, fileName);

    return rootEntity;
}

// light //
DirectionalLightComponent *SceneManager::createDirectionalLight(const std::string& name, Entity* parent)
{
    std::string resultName = name.empty() ? "directional_light" : name;
    Entity *newEntity = this->createEntity(resultName, parent);

    return newEntity->addComponent<DirectionalLightComponent>();
}

PointLightComponent *SceneManager::createPointLight(const std::string& name, Entity* parent)
{
    std::string resultName = name.empty() ? "point_light" : name;
    Entity *newEntity = this->createEntity(resultName, parent);

    return newEntity->addComponent<PointLightComponent>();
}

CameraComponent *SceneManager::getMainCamera()
{
	return SingletonsManager::getInstance()->resolve<RenderManager>()->getMainCamera();
}

Entity *SceneManager::createMeshEntity(MeshData* objectData, const std::string& name, Entity* parent)
{
    Entity *newEntity = this->createEntity(name, parent);
	newEntity->addComponent<MeshComponent>(objectData);
    return newEntity;
}

} // namespace
