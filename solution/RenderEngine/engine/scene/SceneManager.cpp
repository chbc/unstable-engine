#include "SceneManager.h"

#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/entities/components/meshes/MeshFactory.h>
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

SceneManager::SceneManager()
{
	this->nodeCount = 0;
	this->mainCamera = UPTR<Entity>{ new Entity };
	this->mainCamera->addComponent<CameraComponent>();
}

SceneManager::~SceneManager()
{
	this->renderableEntities.clear();
}

Entity *SceneManager::addCubeEntity(float size)
{
	Entity *newEntity = new Entity;
	MeshFactory::createCube(newEntity, size);
	
	this->renderableEntities.emplace_back(newEntity);

	return newEntity;
}

Entity *SceneManager::addPlaneEntity(float size)
{
	Entity *newEntity = new Entity;
	MeshFactory::createPlane(newEntity, size);
	
	this->renderableEntities.emplace_back(newEntity);

	return newEntity;
}

Entity *SceneManager::addModelEntity(const char *fileName)
{
    /* ### TODO: implementar
    RenderableNode *newNode = new ModelNode(this, fileName);
    this->renderableNodes.push_back(newNode);

    return newNode;
    */

    return nullptr;
}
//

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
	return this->mainCamera->getComponent<CameraComponent>();
}

void SceneManager::render(RenderManager *renderManager)
{
    // Camera
	CameraComponent *cameraComponent = this->mainCamera->getComponent<CameraComponent>();
	renderManager->renderCamera
	(
		this->mainCamera->getTransform()->getPosition(), 
		cameraComponent->lookAtTarget, cameraComponent->up
	);

    // Entities
	for (const UPTR<Entity> &item : this->renderableEntities)
		renderManager->render(item);
}

int SceneManager::generateNodeId()
{
	int newId = this->nodeCount;
	this->nodeCount++;

	return newId;
}

} // namespace
