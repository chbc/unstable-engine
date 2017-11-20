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

	SingletonsManager::getInstance()->resolve<RenderManager>()->setMainCamera(cameraComponent);
}

SceneManager::~SceneManager()
{
	this->entities.clear();
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
	return modelLoader.load(fileName);
}

// light //
DirectionalLightComponent *SceneManager::addDirectionalLight()
{
	Entity *newEntity = this->createEntity();
	RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
	return renderManager->addDirectionalLight(newEntity);
}

PointLightComponent *SceneManager::addPointLight()
{
	Entity *newEntity = this->createEntity();
	RenderManager *renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
	return renderManager->addPointLight(newEntity);
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
