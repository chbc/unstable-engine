#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorFileBrowser.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "Paths.h"
#include "EditorsController.h"

#include "imgui/imgui.h"

namespace sre
{

EditorFileBrowser::EditorFileBrowser(EditorsController* arg_controller) 
{
	this->controller = arg_controller;
}

void EditorFileBrowser::onInit()
{
	this->controller->refreshFileItems(Paths().ENGINE_MEDIA_FOLDER, this->fileItems);
}

void EditorFileBrowser::onEditorGUI()
{
	ImGui::Begin("File Browser");
	const ImVec2 size{ 64, 64 };

	ImGui::BeginTable("files", 10);

	ImGui::TableNextRow();
	for (const auto& item : this->fileItems)
	{
		ImGui::TableNextColumn();
		ImGui::ImageButton(item->textureId, size);
		ImGui::Text(item->fileName.c_str());
	}
	ImGui::EndTable();

	ImGui::End();
}

} // namespace

#endif
