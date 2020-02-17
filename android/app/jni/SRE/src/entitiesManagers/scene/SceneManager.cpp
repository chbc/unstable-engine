#include "SceneManager.h"

#include "CameraComponent.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "ModelLoader.h"
#include "MeshComponent.h"

namespace sre
{

SceneManager::SceneManager() : AEntityManager()
{
    Entity *mainCamera = this->createEntity();
    CameraComponent *cameraComponent = mainCamera->addComponent<CameraComponent>();
    this->addEntity(mainCamera, "_main_camera");

    SingletonsManager::getInstance()->resolve<RenderManager>()->setMainCamera(cameraComponent);
}

Entity *SceneManager::createPlaneEntity(float size)
{
	return this->createMeshEntity(PrimitiveMeshFactory().createPlane(size));
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

Entity *SceneManager::createMeshEntity(MeshData<VertexData> *objectData)
{
    Entity *newEntity = this->createEntity();
	newEntity->addComponent<MeshComponent>(objectData);
    return newEntity;
}

} // namespace
