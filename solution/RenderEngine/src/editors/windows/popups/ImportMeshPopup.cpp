#include "ImportMeshPopup.h"
#include "EditorsController.h"

namespace sre
{

float ImportMeshPopup::scaleFactor{1.0f};
bool ImportMeshPopup::loadToScene{ true };
bool ImportMeshPopup::importMaterials{ true };

ImportMeshPopup::ImportMeshPopup(Action_OnClosePopup* onCloseAction, std::string arg_sourceFilePath, std::string arg_destinationPath)
	: AEditorPopup(onCloseAction), sourceFilePath(arg_sourceFilePath), destinationPath(arg_destinationPath)
{ }

void ImportMeshPopup::onEditorGUI()
{
	ImGui::OpenPopup("Import Mesh");

	if (ImGui::BeginPopupModal("Import Mesh", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		std::string title{ "Source: " + sourceFilePath };
		ImGui::Text(title.c_str());
		ImGui::Separator();

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		ImGui::Checkbox("Load to scene", &loadToScene);
		ImGui::PopStyleVar();

		ImGui::DragFloat("Scale factor", &scaleFactor, 0.01f, 0.001f, 1000.0f, "%.3f");

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		ImGui::Checkbox("Import materials", &importMaterials);
		ImGui::PopStyleVar();

		if (ImGui::Button("OK", ImVec2(120, 0)))
		{
			AEditorPopup::close(true);
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(120, 0)))
		{
			AEditorPopup::close(false);
		}
		ImGui::EndPopup();
	}
}

} // namespace
