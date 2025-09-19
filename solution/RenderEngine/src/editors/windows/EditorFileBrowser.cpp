#if !defined(__ANDROID__)

#include "EditorFileBrowser.h"
#include "SingletonsManager.h"
#include "EditorsController.h"
#include "FileUtils.h"
#include "MessagesManager.h"
#include "EditorMessages.h"

#include "imgui.h"

namespace sre
{

EditorFileBrowser::EditorFileBrowser(EditorsController* arg_controller) 
{
	this->controller = arg_controller;
	this->entitySelectionAction = SPTR<Action>(new Action([&](void* message) { this->onEntitySelected(message); }));
	this->refreshIconsAction = SPTR<Action>(new Action([&](void* message) { this->refreshFileIcons(); }));
}

void EditorFileBrowser::onInit()
{
	this->gameContentFolder = FileUtils::getContentAbsolutePath("game");
	this->engineContentFolder = FileUtils::getContentAbsolutePath("engine");
	this->controller->setCurrentDirectory(this->gameContentFolder);
	this->refreshFileIcons();
	this->externalFileDropHandler.onInit(this->controller, this);
	this->contextMenu.onInit(this->controller);

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<EntitySelectionMessage>(this->entitySelectionAction.get());
	messagesManager->addListener<RefreshFileIconsMessage>(this->refreshIconsAction.get());
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
			this->controller->setCurrentDirectory(item->filePath);
			this->refreshFileIcons();
			break;
		}
	}

	this->contextMenu.onEditorGUI();

	this->handleDelete();

	ImGui::End();
}

void EditorFileBrowser::onCleanUp()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->removeListener<EntitySelectionMessage>(this->entitySelectionAction.get());
	messagesManager->removeListener<RefreshFileIconsMessage>(this->refreshIconsAction.get());

	this->externalFileDropHandler.onCleanUp();
}

void EditorFileBrowser::refreshFileIcons()
{
	this->controller->refreshFileIcons(this->fileIcons);
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
		this->controller->setCurrentDirectory(this->gameContentFolder);
		this->refreshFileIcons();
	}

	ImGui::SameLine();

	if (ImGui::Button("Engine", ImVec2{ 64, 16 }))
	{
		this->controller->setCurrentDirectory(this->engineContentFolder);
		this->refreshFileIcons();
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
		this->controller->deleteFile(this->selectedItem->filePath.c_str());
		this->refreshFileIcons();
	}
}

void EditorFileBrowser::handleDuplicate()
{
	if (this->selectedItem && ImGui::IsKeyPressed(ImGuiKey_D) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
	{
		this->controller->duplicateFile(this->selectedItem->filePath.c_str());
		this->refreshFileIcons();
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

void EditorFileBrowser::onEntitySelected(void* data)
{
	this->selectedItem = nullptr;
}

} // namespace

#endif
