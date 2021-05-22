#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorEntityProperties.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "Entity.h"

#include "imgui/imgui.h"

namespace sre
{

EditorEntityProperties::EditorEntityProperties() : entity(nullptr)
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
	Action action = [&](void* message) { this->onEntitySelected(message); };
	messagesManager->addListener<EntitySelectionMessage>(action);
}

void EditorEntityProperties::onEditorGUI()
{
	if 
	(
		(this->entity != nullptr) &&
		ImGui::CollapsingHeader("Properties", ImGuiTreeNodeFlags_DefaultOpen)
	)
	{
		for (const auto& component : this->entity->componentsMap)
		{
			const char* componentName = component.second->getClassName();
			if (ImGui::TreeNodeEx(componentName, ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (const auto& property : component.second->editorProperties)
				{
					property->draw();
				}
				ImGui::Separator();
				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
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
