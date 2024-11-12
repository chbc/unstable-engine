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
		for (const auto& component : this->entity->componentsMap)
		{
			const char* componentName = component.second->getClassName();
			if (ImGui::CollapsingHeader(componentName, ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (const auto& property : component.second->editorProperties)
				{
					property->draw();
				}
				// ImGui::Separator();
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
