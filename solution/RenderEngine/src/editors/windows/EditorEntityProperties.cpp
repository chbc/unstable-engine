#if !defined(__ANDROID__)

#include "EditorEntityProperties.h"
#include "Entity.h"
#include "EditorsController.h"

#include "imgui.h"

namespace sre
{

EditorEntityProperties::EditorEntityProperties(EditorsController* arg_controller)
	: controller(arg_controller)
{ }

void EditorEntityProperties::onEditorGUI()
{
	ImGui::Begin("Properties");

	Entity* entity = this->controller->getSelectedEntity();

	if (entity != nullptr)
	{
		ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoHostExtendX;

		if (ImGui::BeginTable("Entity Properties", 2, flags))
		{
			for (const auto& property : entity->editorProperties)
			{
				ImGui::TableNextRow();
				property->draw();
			}

			ImGui::EndTable();
		}

		for (const auto& component : entity->componentsMap)
		{
			const char* componentName = component.second->getClassName();

			if (ImGui::CollapsingHeader(componentName, ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::BeginTable("Component Properties", 2, flags))
				{
					for (const auto& property : component.second->editorProperties)
					{
						ImGui::TableNextRow();
						property->draw();
					}

					ImGui::EndTable();
				}
			}
		}
	}

	ImGui::End();
}

} // namespace

#endif
