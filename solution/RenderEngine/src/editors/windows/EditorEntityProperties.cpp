#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorEntityProperties.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "Entity.h"

#include "imgui.h"

namespace sre
{

EditorEntityProperties::EditorEntityProperties() : entity(nullptr)
{
	Action* action = new Action{ [&](void* message) { this->onEntitySelected(message); } };
	this->selectionAction = SPTR<Action>(action);
}

void EditorEntityProperties::onInit()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<EntitySelectionMessage>(this->selectionAction.get());
	this->entity = nullptr;
}

void EditorEntityProperties::onEditorGUI()
{
	ImGui::Begin("Properties");

	if (this->entity != nullptr)
	{
		ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoHostExtendX;

		if (ImGui::BeginTable("Entity Properties", 2, flags))
		{
			for (const auto& property : this->entity->editorProperties)
			{
				ImGui::TableNextRow();
				property->draw();
			}

			ImGui::EndTable();
		}

		for (const auto& component : this->entity->componentsMap)
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

void EditorEntityProperties::onCleanUp()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->removeListener<EntitySelectionMessage>(this->selectionAction.get());
	this->entity = nullptr;
}

void EditorEntityProperties::onRelease()
{
	this->entity = nullptr;
}

void EditorEntityProperties::onEntitySelected(void* data)
{
	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);
	this->entity = message->entity;
}

} // namespace

#endif
