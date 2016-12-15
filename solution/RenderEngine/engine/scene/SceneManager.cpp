#include "SceneManager.h"

/*
#include <engine/entities/renderables/CubeNode.h>
#include <engine/entities/renderables/PlaneNode.h>
#include <engine/entities/lights/DirectionalLight.h>
#include <engine/systems/graphics/RenderManager.h>
*/

#include <engine/entities/components/cameras/CameraComponent.h>

namespace sre
{

// ### IMPLEMENT_SINGLETON(SceneManager);

SceneManager::SceneManager()
{
	this->nodeCount = 0;
	this->mainCamera = UPTR<Entity>{ new Entity };
	this->mainCamera->addComponent<CameraComponent>();
}

SceneManager::~SceneManager()
{
	this->entities.clear();
}

Entity *SceneManager::addCubeEntity(float size)
{
	UPTR<Entity> newEntity = UPTR<Entity>{ new Entity };
	// ### newEntity->addComponent		new CubeNode(size);
	
	this->entities.push_back(std::move(newEntity));

	return newEntity.get();
}

Entity *SceneManager::addPlaneEntity(float size)
{
	UPTR<Entity> newEntity = UPTR<Entity>{ new Entity };
	// ### this->renderableNodes.push_back(newNode);

	return newEntity.get();
}

Entity *SceneManager::addModelEntity(const char *fileName)
{
    /* TODO: implementar
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

Entity *SceneManager::getMainCamera()
{
	return this->mainCamera.get();
}

void SceneManager::render()
{
	/*
    RenderManager *renderManager = RenderManager::getInstance();

    // Camera
	renderManager->renderCamera(this->mainCamera->getTransform()->getPosition(), this->mainCamera->lookTarget, this->mainCamera->up);

    // Nodes
    renderManager->render(this->renderableNodes);
	*/
}

int SceneManager::generateNodeId()
{
	int newId = this->nodeCount;
	this->nodeCount++;

	return newId;
}

} // namespace
