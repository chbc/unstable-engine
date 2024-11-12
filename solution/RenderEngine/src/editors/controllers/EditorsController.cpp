#include "EditorsController.h"
#include "RenderEngine.h"
#include "ScenesManager.h"

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
	this->scenesManager->createMeshEntity("cube", "cube.mesh");
}

void EditorsController::createPlane()
{
	this->scenesManager->createMeshEntity("plane", "plane.mesh");
}

} // namespace
