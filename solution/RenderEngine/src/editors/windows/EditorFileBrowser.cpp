#if !defined(__ANDROID__)

#include "EditorFileBrowser.h"
#include "SingletonsManager.h"
#include "EditorsController.h"
#include "FileUtils.h"
#include "MessagesManager.h"
#include "EditorMessages.h"

#include "imgui.h"
#include <sstream>

namespace sre
{

EditorFileBrowser::EditorFileBrowser(EditorsController* arg_controller) 
{
	this->controller = arg_controller;
	this->externalFileDropAction = SPTR<Action>(new Action([&](void* message) { this->handleExternalFileDrop(message); }));
	this->entitySelectionAction = SPTR<Action>(new Action([&](void* message) { this->onEntitySelected(message); }));
}

void EditorFileBrowser::onInit()
{
	this->gameContentFolder = FileUtils::getContentAbsolutePath("game");
	this->engineContentFolder = FileUtils::getContentAbsolutePath("engine");
	this->currentDirectory = this->gameContentFolder;
	this->controller->refreshFileIcons(this->gameContentFolder, this->fileIcons);

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<FileDropEditorMessage>(this->externalFileDropAction.get());
	messagesManager->addListener<EntitySelectionMessage>(this->entitySelectionAction.get());
}

void EditorFileBrowser::onEditorGUI()
{
	ImGui::Begin("File Browser");
	this->showRootContentButtons();

	const ImVec2 size{ 64, 64 };
	this->setupColumns(size);

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
	{
		this->selectedItem = nullptr;
	}

	for (int i = 0; i < this->fileIcons.size(); ++i)
	{
		FileIcon* item = this->fileIcons[i].get();
		
		ImGui::PushID(item->filePath.c_str());

		bool directoryChanged = false;

		this->showIcon(item, size);

		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			EAssetType assetType = FileUtils::getAssetType(item->filePath);
			switch (assetType)
			{
				case EAssetType::DIRECTORY:
					directoryChanged = true;
					break;
				case EAssetType::SCENE:
					this->controller->loadFileFromBrowser(item->filePath.c_str());
					break;
				default: break;
			}
		}

		this->handleIconDrag(item, size);

		ImGui::PopID();

		ImGui::TextWrapped(item->fileName.c_str());
		ImGui::NextColumn();

		if (directoryChanged)
		{
			this->currentDirectory = item->filePath;
			this->controller->refreshFileIcons(item->filePath, this->fileIcons);
			break;
		}
	}

	this->handleDelete();

	ImGui::End();
}

void EditorFileBrowser::onCleanUp()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->removeListener<FileDropEditorMessage>(this->externalFileDropAction.get());
	messagesManager->removeListener<EntitySelectionMessage>(this->entitySelectionAction.get());
}

void EditorFileBrowser::setupColumns(const ImVec2& iconSize)
{
	float padding = 16;
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columns = static_cast<int>(panelWidth / (iconSize.x + padding));
	if (columns < 1)
	{
		columns = 1;
	}

	ImGui::Columns(columns, 0, false);
}

void EditorFileBrowser::showRootContentButtons()
{
	if (ImGui::Button("Content", ImVec2{ 64, 16 }))
	{
		this->controller->refreshFileIcons(this->gameContentFolder, this->fileIcons);
	}

	ImGui::SameLine();

	if (ImGui::Button("Engine", ImVec2{ 64, 16 }))
	{
		this->controller->refreshFileIcons(this->engineContentFolder, this->fileIcons);
	}
}

void EditorFileBrowser::showIcon(FileIcon* icon, const ImVec2& size)
{
	const ImVec4& HoveredColor = ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered);
	ImVec4 IconColor = (icon == this->selectedItem) ? HoveredColor : ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f };

	ImGui::PushStyleColor(ImGuiCol_Button, IconColor);
	if (ImGui::ImageButton(icon->fileName.c_str(), icon->textureId, size))
	{
		this->controller->setSelectedEntity(nullptr);
		this->selectedItem = icon;
	}
	ImGui::PopStyleColor();
}

void EditorFileBrowser::handleDelete()
{
	if (this->selectedItem && ImGui::IsKeyPressed(ImGuiKey_Delete))
	{
		EAssetType assetType = FileUtils::getAssetType(this->selectedItem->filePath);
		this->controller->deleteFile(this->selectedItem->filePath.c_str(), assetType == EAssetType::DIRECTORY);
		this->controller->refreshFileIcons(this->currentDirectory, this->fileIcons);
	}
}

void EditorFileBrowser::handleIconDrag(FileIcon* icon, const ImVec2& size)
{
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("FILE", icon->filePath.c_str(), icon->filePath.size() + 1);
		ImGui::Image(icon->textureId, size);
		ImGui::EndDragDropSource();
	}
}

void EditorFileBrowser::handleExternalFileDrop(void* message)
{
	FileDropEditorMessage* fileDropMessage = static_cast<FileDropEditorMessage*>(message);

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
				this->controller->refreshFileIcons(this->currentDirectory, this->fileIcons);

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
	
	ImportMeshPopup* importPopup = new ImportMeshPopup { this->onClosePopupAction.get(), fileDropMessage->filePath, this->currentDirectory};
	ShowPopupEditorMessage popupMessage{ importPopup };
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->notify(&popupMessage);
}

void EditorFileBrowser::onEntitySelected(void* data)
{
	this->selectedItem = nullptr;
}

} // namespace

#endif
