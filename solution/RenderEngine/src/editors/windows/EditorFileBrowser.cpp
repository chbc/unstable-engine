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
	this->gameContentFolder = FileUtils::getAbsoluteContentPath("game");
	this->controller->refreshFileIcons(this->gameContentFolder, this->fileIcons);
}

void EditorFileBrowser::onEditorGUI()
{
	ImGui::Begin("File Browser");
	if (ImGui::Button("Content", ImVec2{ 64, 16 }))
	{
		this->controller->refreshFileIcons(this->gameContentFolder, this->fileIcons);
	}

	ImGui::BeginTable("files", 10);
	const ImVec2 size{ 64, 64 };

	ImGui::TableNextRow();
	for (int i = 0; i < this->fileIcons.size(); ++i)
	{
		FileIcon* item = this->fileIcons[i].get();
		ImGui::TableNextColumn();
		if (ImGui::ImageButton(item->textureId, size))
		{
			if (FileUtils::isDirectory(item->filePath))
			{
				this->controller->refreshFileIcons(item->filePath, this->fileIcons);
				break;
			}
		}
		ImGui::Text(item->filePath.c_str());
	}
	ImGui::EndTable();

	ImGui::End();
}

} // namespace

#endif
