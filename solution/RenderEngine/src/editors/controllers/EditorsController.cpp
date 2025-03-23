#include "EditorsController.h"
#include "RenderEngine.h"
#include "ScenesManager.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "MultimediaManager.h"
#include "FileUtils.h"
#include "AssetsManager.h"
#include "Texture.h"
#include "EntityLoader.h"

namespace sre
{

EditorsController::EditorsController(ScenesManager* arg_scenesManager)
	: scenesManager(arg_scenesManager)
{ }

void EditorsController::openScene()
{
	std::string resultFileName;
	MultimediaManager::openFileDialog("Open Scene", "Scene Files (*.scene)\0*.scene\0", resultFileName);

	if (!resultFileName.empty())
	{
		RenderEngine::getInstance()->loadScenes(resultFileName, "DefaultGui");
	}
}

void EditorsController::openGui()
{
}

void EditorsController::saveScene()
{
	this->scenesManager->saveScenes();
}

void EditorsController::saveGui()
{
}

void EditorsController::createCube()
{
	this->createMeshEntity("cube", "Cube.mesh");
}

void EditorsController::createPlane()
{
	this->createMeshEntity("plane", "Plane.mesh");
}

void EditorsController::createSphere()
{
	this->createMeshEntity("sphere", "Sphere.mesh");
}

void EditorsController::createGUIImage()
{
	Entity* newEntity = this->scenesManager->createGUIImageEntity("whiteTexture.png");
	this->notifyNewEntity(newEntity);
}

void EditorsController::refreshFileIcons(std::string directoryPath, std::vector<UPTR<FileIcon>>& result)
{
	result.clear();
	std::vector<std::string> iconPaths;
	std::vector<std::string> filePaths;
	FileUtils::getFileAndIconPaths(directoryPath, iconPaths, filePaths);

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

void EditorsController::saveEntity(Entity* entity)
{
	std::string filePath{ entity->filePath };
	if (filePath.empty())
	{
		filePath = entity->getName();
		entity->filePath = filePath;
	}

	EntityLoader().save(entity, filePath.c_str());
}

void EditorsController::createMeshEntity(const char* name, const char* file)
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
