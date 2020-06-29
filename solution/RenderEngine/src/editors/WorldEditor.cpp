#include "WorldEditor.h"

#include "thirdParties/imgui/imgui.h"

namespace sre
{

void WorldEditor::onGUI()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New scene");
			ImGui::MenuItem("Open scene");
			ImGui::MenuItem("Save scene");
			ImGui::MenuItem("Save scene as");
			ImGui::MenuItem("Exit");
			
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::EndMenu();
		}
		
		ImGui::EndMenuBar();
	}
}
	
} // namespace
