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

void EditorsController::newScene()
{
	const char* defaultScene = "engine\\scenes\\Default.scene";
	RenderEngine::getInstance()->loadScene(defaultScene);
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
	if (this->scenesManager->isSceneStored())
	{
		this->scenesManager->saveScene();
	}
	else
	{
		std::string resultFilePath;
		MultimediaManager::saveFileDialog("Save Scene", "Scene Files (*.scene)\0*.scene\0", resultFilePath);
		if (!resultFilePath.empty())
		{
			this->scenesManager->saveScene(resultFilePath);
		}
	}
}

void EditorsController::saveGui()
{
	if (this->scenesManager->isGuiSceneStored())
	{
		this->scenesManager->saveGuiScene();
	}
	else
	{
		std::string resultFilePath;
		MultimediaManager::saveFileDialog("Save GUI", "Gui Files (*.gui)\0*.gui\0", resultFilePath);
		if (!resultFilePath.empty())
		{
			this->scenesManager->saveGuiScene(resultFilePath);
		}
	}
}

void EditorsController::createGUIImage()
{
	Entity* newEntity = this->scenesManager->createGUIImageEntity(GUI_IMAGE_PATH);
	this->setSelectedEntity(newEntity);
}

void EditorsController::createGUIText()
{
	Entity* newEntity = this->scenesManager->createGUITextEntity(TEXT_FONT_PATH);
	this->setSelectedEntity(newEntity);
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
		Texture* texture = assetsManager->loadIcon(icon.c_str());
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

void EditorsController::loadFileFromBrowser(const char* filePath)
{
	EAssetType fileType = FileUtils::getAssetType(filePath);
	switch (fileType)
	{
		case EAssetType::SCENE:
			RenderEngine::getInstance()->loadScene(filePath);
			break;
		case EAssetType::MESH:
		{
			std::string name = FileUtils::getFileName(filePath);
			this->createMeshEntity(filePath, name.c_str());
			break;
		}

		default: break;
	}
}

void EditorsController::importMesh(const char* sourceFilePath, const char* destinationPath,
	float scaleFactor, bool importMaterials, std::string& resultFilePath)
{
	std::stringstream commandStream;
	std::string toolPath = FileUtils::getToolsAbsolutePath("MeshConverter.exe");
	int importMaterialsParam = importMaterials ? 1 : 0;
	commandStream << toolPath << " " << sourceFilePath << " " << destinationPath
		<< " " << scaleFactor << " " << importMaterialsParam;
	std::string command = commandStream.str();

	system(command.c_str());

	std::string fileName = FileUtils::getFileName(sourceFilePath);
	std::stringstream resultStream;
	resultStream << destinationPath << "\\" << fileName << ".mesh";
	resultFilePath = resultStream.str();

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	MeshImportedEditorMessage message{ sourceFilePath, scaleFactor };
	messagesManager->notify(&message);
}

void EditorsController::createMeshEntity(const char* file, const char* meshName)
{
	Entity* newEntity = this->scenesManager->createMeshEntity(file, meshName);
	this->setSelectedEntity(newEntity);

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	MeshEntityLoadedEditorMessage message{ newEntity, file };
	messagesManager->notify(&message);
}

void EditorsController::createDirectionalLight()
{
	this->scenesManager->createDirectionalLight();
}

void EditorsController::createPointLight()
{
	this->scenesManager->createPointLight();
}

void EditorsController::setSelectedEntity(Entity* entity)
{
	this->selectedEntity = entity;
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	EntitySelectionMessage message{ entity };
	messagesManager->notify(&message);
}

Entity* EditorsController::getSelectedEntity()
{
	return this->selectedEntity;
}

void EditorsController::deleteFile(const char* filePath, bool isDirectory)
{
	std::stringstream commandStream;
	std::string delCommand = isDirectory ? "rmdir /S/Q" : "del /F/Q";
	commandStream << delCommand << " " << filePath;
	std::string command = commandStream.str();

	system(command.c_str());
}

} // namespace
