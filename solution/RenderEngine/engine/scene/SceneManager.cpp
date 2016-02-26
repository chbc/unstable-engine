#include "SceneManager.h"
#include <engine/nodes/renderables/CubeNode.h>
#include <engine/nodes/renderables/PlaneNode.h>
#include <engine/nodes/lights/DirectionalLight.h>
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

IMPLEMENT_SINGLETON(SceneManager);

SceneManager::SceneManager()
{
}

bool SceneManager::init()
{
	this->nodeCount = 0;
	this->mainCamera = new CameraNode();

	return true;
}

void SceneManager::release()
{
	// release renderables nodes //
	std::vector<RenderableNode *>::iterator it = this->renderableNodes.begin();
	while(it != this->renderableNodes.end())
	{
		delete (*it);
		it++;
	}
	this->renderableNodes.clear();

	// release main camera //
	delete this->mainCamera;
}

int SceneManager::generateNodeId()
{
	int newId = this->nodeCount;
	this->nodeCount++;

	return newId;
}

void SceneManager::render()
{
    RenderManager *renderManager = RenderManager::getInstance();

    // Camera
	renderManager->renderCamera(this->mainCamera->getTransform()->getPosition(), this->mainCamera->lookTarget, this->mainCamera->up);

    // Nodes
    renderManager->render(this->renderableNodes);
}

// Nodes //
RenderableNode *SceneManager::addCubeNode(float size)
{
	RenderableNode *newNode = new CubeNode(size);
	this->renderableNodes.push_back(newNode);

	return newNode;
}

RenderableNode *SceneManager::addPlaneNode(float size)
{
	RenderableNode *newNode = new PlaneNode(size);
	this->renderableNodes.push_back(newNode);

	return newNode;
}

RenderableNode *SceneManager::addModelNode(const char *fileName)
{
    /* TODO: implementar
    RenderableNode *newNode = new ModelNode(this, fileName);
    this->renderableNodes.push_back(newNode);

    return newNode;
    */

    return NULL;
}
//

// light //
DirectionalLight *SceneManager::addDirectionalLight()
{
    RenderManager *renderManager = RenderManager::getInstance();
    return renderManager->addDirectionalLight();
}

PointLight *SceneManager::addPointLight()
{
    RenderManager *renderManager = RenderManager::getInstance();
    return renderManager->addPointLight();
}

// Camera
CameraNode *SceneManager::getMainCamera()
{
	return this->mainCamera;
}
//
} // namespace
