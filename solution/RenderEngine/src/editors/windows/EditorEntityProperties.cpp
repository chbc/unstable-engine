#if !defined(__ANDROID__)

#include "EditorEntityProperties.h"
#include "Entity.h"
#include "EditorsController.h"
#include "EntityComponentTypes.h"

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
			std::string componentName = component.second->getClassName();
			if (componentName != "GuizmoComponent")
			{
				if (ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
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

		this->drawAddComponentButton(entity);
	}


	ImGui::End();
}

void EditorEntityProperties::drawAddComponentButton(Entity* selectedEntity)
{
	ImGui::Separator();

	if (ImGui::Button("[+] Add Component"))
	{
		this->addingComponent = true;
	}

	if (this->addingComponent)
	{
		EntityComponentTypes* componentTypes = EntityComponentTypes::getInstance();
		const std::vector<const char*>& classNames = componentTypes->getClassNames();

		if (ImGui::Combo("##Components", &this->currentAddedComponent, classNames.data(), classNames.size()))
		{
			if (this->currentAddedComponent != 0)
			{
				selectedEntity->addComponent(classNames[this->currentAddedComponent]);
			}

			this->addingComponent = false;
			this->currentAddedComponent = 0;
		}
	}

	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		this->addingComponent = false;
	}
}

} // namespace

#endif
