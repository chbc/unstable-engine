#include "SceneManager.h"

#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/entities/components/meshes/MeshFactory.h>
#include <engine/systems/graphics/RenderManager.h>
#include <engine/systems/io/ModelLoader.h>

namespace sre
{

SceneManager::SceneManager()
{
	this->nodeCount = 0;
	Entity *mainCamera = new Entity;
	CameraComponent *cameraComponent = mainCamera->addComponent<CameraComponent>();

	RenderManager::getInstance()->setMainCamera(cameraComponent);
	this->entities.emplace_back(mainCamera);
}

SceneManager::~SceneManager()
{
	this->entities.clear();
}

Entity *SceneManager::createPlaneEntity(float size)
{
	Entity *newEntity = new Entity;
	MeshComponent *mesh = MeshFactory::createPlane(newEntity, size);
	return newEntity;
}

Entity *SceneManager::createCubeEntity(float size)
{
	Entity *newEntity = new Entity;
	MeshComponent *mesh = MeshFactory::createCube(newEntity, size);
	return newEntity;
}

Entity *SceneManager::createModelEntity(const std::string &fileName)
{
	ModelLoader modelLoader;
	return modelLoader.load(fileName);
}

void SceneManager::addEntity(Entity *newEntity)
{
	this->entities.emplace_back(newEntity);
	RenderManager::getInstance()->addEntity(newEntity);
}

// light //
DirectionalLightComponent *SceneManager::addDirectionalLight()
{
	Entity *newEntity = new Entity;
	RenderManager *renderManager = RenderManager::getInstance();

	this->entities.emplace_back(newEntity);
	return renderManager->addDirectionalLight(newEntity);
}

PointLightComponent *SceneManager::addPointLight()
{
	Entity *newEntity = new Entity;
	RenderManager *renderManager = RenderManager::getInstance();

	this->entities.emplace_back(newEntity);
	return renderManager->addPointLight(newEntity);
}

CameraComponent *SceneManager::getMainCamera()
{
	return RenderManager::getInstance()->getMainCamera();
}

int SceneManager::generateNodeId()
{
	int newId = this->nodeCount;
	this->nodeCount++;

	return newId;
}

} // namespace
