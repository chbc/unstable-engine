#include "EditorsController.h"
#include "RenderEngine.h"
#include "ScenesManager.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "TextureManager.h"
#include "Paths.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace sre
{

EditorsController::EditorsController(ScenesManager* arg_scenesManager)
	: scenesManager(arg_scenesManager)
{ }

void EditorsController::init()
{
	if (this->textureManager == nullptr)
	{
		this->textureManager = SingletonsManager::getInstance()->get<TextureManager>();
	}
}

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

void EditorsController::refreshFileItems(const char* directoryPath, std::vector<UPTR<FileItem>>& result)
{
	result.clear();
	Paths paths;
	for (const auto& item : fs::directory_iterator(directoryPath))
	{
		std::string iconName;
		const auto& extension = item.path().extension();
		if (item.is_directory())
		{
			iconName = "folder_icon";
		}
		else if (extension == ".scene")
		{
			iconName = "scene_icon";
		}
		else if (extension == ".mesh")
		{
			iconName = "mesh_icon";
		}
		else if (extension == ".mat")
		{
			iconName = "material_icon";
		}
		else
		{
			iconName = "unknown_file_icon";
		}

		std::string filePath;
		paths.buildIconFilePath(iconName.c_str(), filePath);
		Texture* texture = this->textureManager->loadGUITexture(filePath);
		void* textureId = reinterpret_cast<void*>(texture->getId());

		FileItem* fileItem = new FileItem{ item.path().filename().string().c_str(), textureId};
		result.emplace_back(fileItem);
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
