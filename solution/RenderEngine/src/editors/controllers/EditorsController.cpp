#include "EditorsController.h"
#include "RenderEngine.h"
#include "ScenesManager.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "FileUtils.h"
#include "AssetsManager.h"
#include "Texture.h"

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

void EditorsController::refreshFileIcons(std::string directoryPath, std::vector<UPTR<FileIcon>>& result)
{
	result.clear();
	std::vector<std::string> iconPaths;
	std::vector<std::string> filePaths;
	FileUtils::getFilePaths(directoryPath, iconPaths, filePaths);

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();

	for (int i = 0; i < filePaths.size(); ++i)
	{
		std::string& icon = iconPaths[i];
		std::string& path = filePaths[i];
		Texture* texture = assetsManager->loadTexture(icon.c_str(), ETextureMap::GUI);
		void* textureId = reinterpret_cast<void*>(texture->getId());

		FileIcon* fileIcon = new FileIcon{path, textureId};
		result.emplace_back(fileIcon);
	}
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
