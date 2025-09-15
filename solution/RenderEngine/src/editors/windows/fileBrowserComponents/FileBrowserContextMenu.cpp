#include "FileBrowserContextMenu.h"
#include "EditorsController.h"

#include "imgui.h"

namespace sre
{

void FileBrowserContextMenu::onInit(EditorsController* arg_controller)
{
	this->controller = arg_controller;
}

void FileBrowserContextMenu::onEditorGUI()
{
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsWindowHovered())
	{
		ImGui::OpenPopup("FILE_BROWSER_CONTEXT");
	}

	if (ImGui::BeginPopup("FILE_BROWSER_CONTEXT"))
	{
		if (ImGui::MenuItem("New Entity"))
		{
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("New Material"))
		{
			this->controller->createMaterial();
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::MenuItem("New Scene"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

} // namespace
