#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorFileBrowser.h"
#include "SingletonsManager.h"
#include "EditorsController.h"
#include "FileUtils.h"

#include "imgui/imgui.h"

namespace sre
{

EditorFileBrowser::EditorFileBrowser(EditorsController* arg_controller) 
{
	this->controller = arg_controller;
}

void EditorFileBrowser::onInit()
{
	this->gameContentFolder = FileUtils::getContentAbsolutePath("game");
	this->controller->refreshFileIcons(this->gameContentFolder, this->fileIcons);
}

void EditorFileBrowser::onEditorGUI()
{
	ImGui::Begin("File Browser");
	if (ImGui::Button("Content", ImVec2{ 64, 16 }))
	{
		this->controller->refreshFileIcons(this->gameContentFolder, this->fileIcons);
	}

	const ImVec2 size{ 64, 64 };

	int padding = 16;
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columns = panelWidth / (size.x + padding);
	if (columns < 1)
	{
		columns = 1;
	}

	ImGui::Columns(columns, 0, false);

	for (int i = 0; i < this->fileIcons.size(); ++i)
	{
		FileIcon* item = this->fileIcons[i].get();
		
		ImGui::PushID(item->filePath.c_str());
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f });

		bool directoryChanged = false;
		ImGui::ImageButton(item->textureId, size);
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

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("FILE", item->filePath.c_str(), item->filePath.size() + 1);
			ImGui::Image(item->textureId, size);
			ImGui::EndDragDropSource();
		}

		ImGui::PopStyleColor();
		ImGui::PopID();

		ImGui::TextWrapped(item->fileName.c_str());
		ImGui::NextColumn();

		if (directoryChanged)
		{
			this->controller->refreshFileIcons(item->filePath, this->fileIcons);
			break;
		}
	}

	ImGui::End();
}

} // namespace

#endif
