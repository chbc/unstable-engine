#include "EditorsController.h"
#include "RenderEngine.h"
#include "SceneLoader.h"
#include "ScenesManager.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "RenderManager.h"

namespace sre
{

EditorsController::EditorsController(ScenesManager* arg_scenesManager)
	: scenesManager(arg_scenesManager)
{ }

void EditorsController::loadScene()
{
	RenderEngine::getInstance()->loadScene("default");
}

void EditorsController::saveScene()
{
	this->scenesManager->saveScenes();
}

void EditorsController::createCube()
{
	/*
	Scene* scene = this->scenesManager->getScene("XXX");
	createMeshEntity(scene, "Cube", "../../media/cube.mesh");
	*/
}

void EditorsController::createPlane()
{
	/*
	Scene* scene = this->scenesManager->getScene("XXX");
	createMeshEntity(scene, "Plane", "../../media/plane.mesh");
	*/
}

void EditorsController::createMeshEntity(Scene* scene, const char* name, const char* filePath)
{
	/* XXX
	Entity* entity = scene->createEntity(name);
	MeshComponent* meshComponent = entity->addComponent<MeshComponent>();

	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	AssetsManager* assetsManager = singletonsManager->get<AssetsManager>();
	MeshData* meshData = assetsManager->loadMesh(filePath);
	meshComponent->mesh->meshData.reset(meshData);
	meshComponent->mesh->fileName = filePath;

	RenderManager* renderManager = singletonsManager->get<RenderManager>();
	renderManager->addEntity(entity);
	renderManager->onSceneLoaded();
	*/
}

} // namespace
