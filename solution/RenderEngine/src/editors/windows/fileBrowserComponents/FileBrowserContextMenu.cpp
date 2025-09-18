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
		bool closePopup = false;

		if (ImGui::MenuItem("New Folder"))
		{
			this->controller->createFolderInCurrentDirectory();
			closePopup = true;
		}
		ImGui::Separator();
		if (ImGui::MenuItem("New Entity"))
		{
			this->controller->createStoredEntity();
			closePopup = true;
		}
		if (ImGui::MenuItem("New Material"))
		{
			this->controller->createMaterial();
			closePopup = true;
		}
		if (ImGui::MenuItem("New Scene"))
		{
			this->controller->createScene();
			closePopup = true;
		}

		if (closePopup)
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

} // namespace
