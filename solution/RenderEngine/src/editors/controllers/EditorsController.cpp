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
{
	this->cubeMeshPath = FileUtils::getAbsoluteContentPath("engine/media/Cube.mesh");
	this->planeMeshPath = FileUtils::getAbsoluteContentPath("engine/media/Plane.mesh");
	this->sphereMeshPath = FileUtils::getAbsoluteContentPath("engine/media/Sphere.mesh");
	this->guiImagePath = FileUtils::getAbsoluteContentPath("engine/media/whiteTexture.png");
}

void EditorsController::openScene()
{
	std::string resultFilePath;
	MultimediaManager::openFileDialog("Open Scene", "Scene Files (*.scene)\0*.scene\0", resultFilePath);

	if (!resultFilePath.empty())
	{
		RenderEngine::getInstance()->loadScene(resultFilePath);
	}
}

void EditorsController::openGui()
{
	std::string resultFilePath;
	MultimediaManager::openFileDialog("Open Gui", "Gui Files (*.gui)\0*.gui\0", resultFilePath);

	if (!resultFilePath.empty())
	{
		RenderEngine::getInstance()->loadGuiScene(resultFilePath);
	}
}

void EditorsController::saveScene()
{
	std::string resultFilePath;
	if (this->scenesManager->isSceneNew())
	{
		MultimediaManager::saveFileDialog("Save Scene", "Scene Files (*.scene)\0*.scene\0", resultFilePath);
	}

	this->scenesManager->saveScene(resultFilePath);
}

void EditorsController::saveGui()
{
	std::string resultFilePath;
	if (this->scenesManager->isGuiSceneNew())
	{
		MultimediaManager::saveFileDialog("Save GUI", "Gui Files (*.gui)\0*.gui\0", resultFilePath);
	}

	this->scenesManager->saveGuiScene(resultFilePath);
}

void EditorsController::createCube()
{
	this->createMeshEntity("cube", this->cubeMeshPath.c_str());
}

void EditorsController::createPlane()
{
	this->createMeshEntity("plane", this->planeMeshPath.c_str());
}

void EditorsController::createSphere()
{
	this->createMeshEntity("sphere", this->sphereMeshPath.c_str());
}

void EditorsController::createGUIImage()
{
	Entity* newEntity = this->scenesManager->createGUIImageEntity(this->guiImagePath);
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
