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

		for (const auto& componentsTuple : entity->componentsMap)
		{
			const auto& componentsList = componentsTuple.second;
			for (int i = 0; i < componentsList.size(); ++i)
			{
				AEntityComponent* component = componentsList[i].get();
				const char* componentName = component->getClassName();
				if (std::strcmp(componentName, "GuizmoComponent") != 0)
				{
					ImGui::PushID(i);
					bool isHeaderOpen = ImGui::CollapsingHeader(componentName, ImGuiTreeNodeFlags_DefaultOpen);
					if (this->drawComponentContextualMenu(component))
					{
						ImGui::PopID();
						break;
					}
					ImGui::PopID();

					if (isHeaderOpen)
					{
						if (ImGui::BeginTable("Component Properties", 2, flags))
						{
							for (const auto& property : component->editorProperties)
							{
								ImGui::TableNextRow();
								property->draw();
							}

							ImGui::EndTable();
						}
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

		int size = static_cast<int>(classNames.size());
		if (ImGui::Combo("##Components", &this->currentAddedComponent, classNames.data(), size))
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

bool EditorEntityProperties::drawComponentContextualMenu(AEntityComponent* component)
{
	bool result = false;
	if (ImGui::BeginPopupContextItem(component->getClassName()))
	{
		if (ImGui::MenuItem("Remove Component"))
		{
			component->destroy();
			ImGui::CloseCurrentPopup();

			result = true;
		}

		ImGui::EndPopup();
	}

	return result;
}

} // namespace

#endif
