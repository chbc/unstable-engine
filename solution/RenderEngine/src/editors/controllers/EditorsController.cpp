#include "EditorsController.h"
#include "RenderEngine.h"
#include "ScenesManager.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"

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
	this->createEntity("cube", "cube.mesh");
}

void EditorsController::createPlane()
{
	this->createEntity("plane", "plane.mesh");
}

void EditorsController::createEntity(const char* name, const char* file)
{
	Entity* newEntity = this->scenesManager->createMeshEntity(name, file);
	this->notifyNewEntity(newEntity);
}

void EditorsController::notifyNewEntity(Entity* entity)
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	EntitySelectionMessage message(entity);
	messagesManager->notify(&message);
}

} // namespace
