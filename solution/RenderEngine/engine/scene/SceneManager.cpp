#include "SceneManager.h"

#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/entities/components/meshes/MeshFactory.h>
#include <engine/systems/graphics/RenderManager.h>

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

Entity *SceneManager::addCubeEntity(float size)
{
	Entity *newEntity = new Entity;
	MeshComponent *mesh = MeshFactory::createCube(newEntity, size);
	
	this->entities.emplace_back(newEntity);
	RenderManager::getInstance()->addMesh(mesh);

	return newEntity;
}

Entity *SceneManager::addPlaneEntity(float size)
{
	Entity *newEntity = new Entity;
	MeshComponent *mesh = MeshFactory::createPlane(newEntity, size);
	
	this->entities.emplace_back(newEntity);
	RenderManager::getInstance()->addMesh(mesh);

	return newEntity;
}

// light //
Entity *SceneManager::addDirectionalLight()
{
	/* ###
    RenderManager *renderManager = RenderManager::getInstance();
    return renderManager->addDirectionalLight();
	*/

	return nullptr;
}

Entity *SceneManager::addPointLight()
{
	/* ###
    RenderManager *renderManager = RenderManager::getInstance();
    return renderManager->addPointLight();
	*/

	return nullptr;
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
