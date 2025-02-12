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

Entity* SceneManager::createPerspectiveCamera(float fov, float near, float far)
{
    Entity* mainCamera = this->createEntity();
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setPerspectiveProjection(fov, EngineValues::SCREEN_WIDTH / EngineValues::SCREEN_HEIGHT, near, far);
    AEntityManager::addEntity(mainCamera, "_main_camera");

    SingletonsManager::getInstance()->resolve<RenderManager>()->setMainCamera(cameraComponent);

    return mainCamera;
}

Entity* SceneManager::createOrthoCamera()
{
    Entity* mainCamera = this->createEntity();
    CameraComponent* cameraComponent = mainCamera->addComponent<CameraComponent>();
    cameraComponent->setOrthoProjection();
    AEntityManager::addEntity(mainCamera, "_main_camera");

    SingletonsManager::getInstance()->resolve<RenderManager>()->setMainCamera(cameraComponent);

    return mainCamera;
}

Entity *SceneManager::createPlaneEntity(const glm::vec2& size, float tileMultiplier)
{
	return this->createMeshEntity(PrimitiveMeshFactory().createPlane(size, tileMultiplier));
}

Entity *SceneManager::createCubeEntity(float size)
{
	return this->createMeshEntity(PrimitiveMeshFactory().createCube(size));
}

Entity *SceneManager::createModelEntity(const std::string &fileName)
{
    ModelLoader modelLoader;
    Entity *rootEntity = this->createEntity();
    modelLoader.load(rootEntity, fileName);

    return rootEntity;
}

// light //
DirectionalLightComponent *SceneManager::addDirectionalLight(const std::string& name)
{
    DirectionalLightComponent *result = nullptr;
    Entity *newEntity = this->createEntity();
    RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
    result = renderManager->addDirectionalLight(newEntity);

    std::string resultName = name.empty() ? "directional_light" : name;
    this->addEntity(newEntity, resultName);
    return result;
}

PointLightComponent *SceneManager::addPointLight(const std::string& name)
{
    PointLightComponent *result = nullptr;
    Entity *newEntity = this->createEntity();

    RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
    result = renderManager->addPointLight(newEntity);

    std::string resultName = name.empty() ? "directional_light" : name;
    this->addEntity(newEntity, resultName);
    return result;
}

CameraComponent *SceneManager::getMainCamera()
{
	return SingletonsManager::getInstance()->resolve<RenderManager>()->getMainCamera();
}

Entity *SceneManager::createMeshEntity(MeshData* objectData)
{
    Entity *newEntity = this->createEntity();
	newEntity->addComponent<MeshComponent>(objectData);
    return newEntity;
}

} // namespace
