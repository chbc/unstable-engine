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
#include "MeshComponent.h"
#include "MaterialLoader.h"
#include "SceneLoader.h"

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
		this->selectedEntity = nullptr;
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
	Entity* newEntity = this->scenesManager->createGUIImageEntity(DEFAULT_GUI_IMAGE_PATH);
	this->setSelectedEntity(newEntity);
}

void EditorsController::createGUIText()
{
	Entity* newEntity = this->scenesManager->createGUITextEntity(DEFAULT_TEXT_FONT_PATH);
	this->setSelectedEntity(newEntity);
}

void EditorsController::refreshFileIcons(std::vector<UPTR<FileIcon>>& result)
{
	result.clear();
	std::vector<std::string> iconPaths;
	std::vector<std::string> filePaths;
	FileUtils::getFileAndIconPaths(this->currentDirectory, iconPaths, filePaths);

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
		filePath = this->currentDirectory + "/" + entity->getName() + ".ent";
		FileUtils::resolveFileNameConflict(filePath);
		entity->filePath = filePath;
	}

	EntityLoader().save(entity, filePath.c_str());
	this->notifyRefreshFileIcons();
}

void EditorsController::loadFileFromBrowser(const std::string& filePath)
{
	EAssetType fileType = FileUtils::getAssetType(filePath);
	switch (fileType)
	{
		case EAssetType::SCENE:
			RenderEngine::getInstance()->loadScene(filePath);
			break;
		case EAssetType::ENTITY:
		{
			Entity* entity = this->scenesManager->createEntityFromFile(filePath);
			this->scenesManager->setupEntityInitialPosition(entity);
			this->scenesManager->addToRenderer(entity);
			this->tryLoadMaterialToEntity(entity, filePath);
			break;
		}
		case EAssetType::MESH:
		{
			std::string name = FileUtils::getFileName(filePath);
			Entity* entity = this->createMeshEntity(filePath, name.c_str());
			this->tryLoadMaterialToEntity(entity, filePath);
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

void EditorsController::copyFileToCurrentDirectory(const std::string& sourceFilePath, const std::string& destinationFileName, bool startRenaming)
{
	std::string resultDestinationFileName = destinationFileName;
	if (resultDestinationFileName.empty())
	{
		resultDestinationFileName = FileUtils::getFileWithExtension(sourceFilePath);
	}

	const std::string resultSourceFilePath = FileUtils::getContentAbsolutePath(sourceFilePath);
	std::string resultDestinationPath = this->currentDirectory + "/" + resultDestinationFileName;
	FileUtils::resolveFileNameConflict(resultDestinationPath);
	FileUtils::copyFile(resultSourceFilePath, resultDestinationPath);

	this->notifyRefreshFileIcons();

	if (startRenaming)
	{
		this->notifyFileRenaming(FileUtils::getFileName(resultDestinationPath));
	}
}

Entity* EditorsController::createMeshEntity(const std::string& filePath, const char* meshName)
{
	Entity* newEntity = this->scenesManager->createMeshEntity(filePath, meshName);
	this->scenesManager->setupEntityInitialPosition(newEntity);
	this->setSelectedEntity(newEntity);

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	MeshEntityLoadedEditorMessage message{ newEntity, filePath };
	messagesManager->notify(&message);

	return newEntity;
}

void EditorsController::createDirectionalLight()
{
	Entity* newEntity = this->scenesManager->createDirectionalLight();
	this->scenesManager->setupEntityInitialPosition(newEntity);
	this->setSelectedEntity(newEntity);
}

void EditorsController::createPointLight()
{
	Entity* newEntity = this->scenesManager->createPointLight();
	this->scenesManager->setupEntityInitialPosition(newEntity);
	this->setSelectedEntity(newEntity);
}

void EditorsController::createSkybox()
{
	Entity* newEntity = this->scenesManager->createSkybox(DEFAULT_SKYBOX_PATH);
	this->setSelectedEntity(newEntity);
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

void EditorsController::duplicateSelectedEntity()
{
	if (this->selectedEntity)
	{
		Entity* sourceEntity = this->selectedEntity;
		this->setSelectedEntity(nullptr);

		Entity* newEntity = this->scenesManager->duplicateEntity(sourceEntity);
		this->setSelectedEntity(newEntity);
	}
}

void EditorsController::deleteFile(const char* filePath)
{
	FileUtils::deleteFile(filePath);
}

void EditorsController::duplicateFile(const std::string& filePath)
{
	FileUtils::duplicateFile(filePath);
}

void EditorsController::renameFile(const std::string& oldFilePath, const std::string& newFileName)
{
	FileUtils::renameFile(oldFilePath, newFileName);
}

void EditorsController::loadMaterialToEntity(Entity* entity, const std::string& materialFilePath)
{
	if (FileUtils::fileExists(materialFilePath))
	{
		std::vector<MeshComponent*> meshComponents;
		entity->getComponents<MeshComponent>(meshComponents);

		for (MeshComponent* meshComponent : meshComponents)
		{
			meshComponent->loadMaterial(materialFilePath.c_str());
		}
	}
}

void EditorsController::createScene()
{
	this->copyFileToCurrentDirectory(DEFAULT_SCENE_PATH, "NewScene.scene", true);
}

void EditorsController::createStoredEntity()
{
	this->copyFileToCurrentDirectory(DEFAULT_ENTITY_PATH, "NewEntity.ent", true);
}

void EditorsController::createMaterial()
{
	this->copyFileToCurrentDirectory(DEFAULT_MATERIAL_PATH, "NewMaterial.mat", true);
}

void EditorsController::notifyRefreshFileIcons() const
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	RefreshFileIconsMessage message;
	messagesManager->notify(&message);
}

void EditorsController::notifyFileRenaming(const std::string& fileName) const
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	RenameFileEditorMessage message{ fileName };
	messagesManager->notify(&message);
}

std::string EditorsController::getCurrentDirectory() const
{
	return this->currentDirectory;
}

void EditorsController::setCurrentDirectory(const std::string& directory)
{
	this->currentDirectory = directory;
	this->notifyRefreshFileIcons();
}

void EditorsController::tryLoadMaterialToEntity(Entity* entity, const std::string& entityPath)
{
	std::string materialFilePath = FileUtils::replaceExtension(entityPath, ".mat");
	this->loadMaterialToEntity(entity, materialFilePath);
}

void EditorsController::createFolderInCurrentDirectory()
{
	std::string folderPath = this->currentDirectory + "/NewFolder";
	FileUtils::resolveFileNameConflict(folderPath);
	FileUtils::createDirectoryIfNotExists(folderPath);
	this->notifyRefreshFileIcons();
}

} // namespace
