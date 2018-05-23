#include "SceneManager.h"

#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/graphics/RenderManager.h>
#include <engine/core/io/ModelLoader.h>
#include <engine/entities/components/meshes/MeshComponent.h>

namespace sre
{

SceneManager::SceneManager() : AEntityManager()
{
    Entity *mainCamera = this->createEntity();
    CameraComponent *cameraComponent = mainCamera->addComponent<CameraComponent>();
    this->addEntity(mainCamera);

    SingletonsManager::getInstance()->resolve<RenderManager>()->setMainCamera(cameraComponent);
}

Entity *SceneManager::createPlaneEntity(float size)
{
    return this->createMeshEntity((PrimitiveMeshFactory()).createPlane(size));
}

Entity *SceneManager::createCubeEntity(float size)
{
    return this->createMeshEntity((PrimitiveMeshFactory()).createCube(size));
}

Entity *SceneManager::createModelEntity(const std::string &fileName)
{
    ModelLoader modelLoader;
    Entity *rootEntity = this->createEntity();
    modelLoader.load(rootEntity, fileName);

    return rootEntity;
}

// light //
DirectionalLightComponent *SceneManager::addDirectionalLight()
{
    DirectionalLightComponent *result = nullptr;
    Entity *newEntity = this->createEntity();
    RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
    result = renderManager->addDirectionalLight(newEntity);

    this->addEntity(newEntity);
    return result;
}

PointLightComponent *SceneManager::addPointLight()
{
    PointLightComponent *result = nullptr;
    Entity *newEntity = this->createEntity();

    RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
    result = renderManager->addPointLight(newEntity);

    this->addEntity(newEntity);
    return result;
}

CameraComponent *SceneManager::getMainCamera()
{
    return SingletonsManager::getInstance()->resolve<RenderManager>()->getMainCamera();
}

Entity *SceneManager::createMeshEntity(UPTR<MeshData<VertexData>> &objectData)
{
    Entity *newEntity = this->createEntity();
    newEntity->addComponent<MeshComponent>(objectData);
    return newEntity;
}

} // namespace
