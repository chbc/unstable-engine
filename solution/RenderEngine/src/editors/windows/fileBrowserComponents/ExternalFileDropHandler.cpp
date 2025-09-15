#include "ExternalFileDropHandler.h"
#include "SingletonsManager.h"
#include "EditorsController.h"
#include "FileUtils.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "EditorFileBrowser.h"
#include "MultimediaManager.h"

namespace sre
{

ExternalFileDropHandler::ExternalFileDropHandler()
{
	this->externalFileDropAction = SPTR<Action>(new Action([&](void* message) { this->handleExternalFileDrop(message); }));
}

void ExternalFileDropHandler::onInit(EditorsController* arg_controller, EditorFileBrowser* arg_fileBrowser)
{
	this->controller = arg_controller;
	this->fileBrowser = arg_fileBrowser;

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<FileDropEditorMessage>(this->externalFileDropAction.get());
}

void ExternalFileDropHandler::onCleanUp()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->removeListener<FileDropEditorMessage>(this->externalFileDropAction.get());
}

void ExternalFileDropHandler::handleExternalFileDrop(void* message)
{
	FileDropEditorMessage* fileDropMessage = static_cast<FileDropEditorMessage*>(message);
	EAssetType assetType = FileUtils::getAssetType(fileDropMessage->filePath);
	if (assetType == EAssetType::SOURCE_MODEL)
	{
		this->handleImportMesh(fileDropMessage->filePath);
	}
	else if (assetType != EAssetType::NONE && assetType != EAssetType::DIRECTORY)
	{
		this->handleCopyFile(fileDropMessage->filePath);
	}
	else
	{
		MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
		multimediaManager->showErrorMessageBox("File Drop Error", "The dropped file type is not supported!");
	}
}

void ExternalFileDropHandler::handleImportMesh(const std::string& sourceFilePath)
{
	Action_OnClosePopup* onClosePopup = new Action_OnClosePopup
	{
		[&](AEditorPopup* popup, bool confirm)
		{
			if (confirm)
			{
				ImportMeshPopup* importPopup = static_cast<ImportMeshPopup*>(popup);
				std::string resultFilePath;
				this->controller->importMesh
				(
					importPopup->sourceFilePath.c_str(), importPopup->destinationPath.c_str(),
					importPopup->scaleFactor, importPopup->importMaterials, resultFilePath
				);
				this->fileBrowser->refreshFileIcons();

				if (importPopup->loadToScene)
				{
					std::string name = FileUtils::getFileName(resultFilePath);
					const char* entityFilePath = resultFilePath.c_str();
					Entity* meshEntity = this->controller->createMeshEntity(entityFilePath, name.c_str());

					if (importPopup->importMaterials)
					{
						std::string materialFilePath = FileUtils::replaceExtension(entityFilePath, ".mat");
						this->controller->loadMaterialToEntity(meshEntity, materialFilePath);
					}
				}
			}
		}
	};

	this->onClosePopupAction = SPTR<Action_OnClosePopup>(onClosePopup);

	std::string currentDirectory = this->controller->getCurrentDirectory();
	ImportMeshPopup* importPopup = new ImportMeshPopup{ this->onClosePopupAction.get(), sourceFilePath, currentDirectory };
	ShowPopupEditorMessage popupMessage{ importPopup };
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->notify(&popupMessage);
}

void ExternalFileDropHandler::handleCopyFile(const std::string& sourceFilePath)
{
	this->controller->copyFile(sourceFilePath, this->controller->getCurrentDirectory());
}

} // namespace sre
