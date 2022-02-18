#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorSceneTree.h"
#include "SingletonsManager.h"
#include "SceneManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "EngineValues.h"

#include "imgui/imgui.h"

namespace sre
{

EditorSceneTree::EditorSceneTree(SceneManager* arg_sceneManager) 
	: sceneManager(arg_sceneManager), selectedEntity(nullptr)
{ }

void EditorSceneTree::onInit()
{
	this->selectedEntity = nullptr;
}

void EditorSceneTree::onEditorGUI()
{
	ImGui::Begin("Hierarchy");

	if (ImGui::CollapsingHeader("scene_name", ImGuiTreeNodeFlags_DefaultOpen))
	{
		for (const auto& item : this->sceneManager->entities)
			this->drawEntityTree(item.second.get(), 0);
	}

	if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
	{
		this->selectedEntity = nullptr;
		MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
		EntitySelectionMessage message(nullptr);
		messagesManager->notify(&message);
	}

	ImGui::End();
}

void EditorSceneTree::drawEntityTree(Entity* entity, int index)
{
	const char* name = entity->getName();
	const uint32_t childrenCount = entity->getChildrenCount();
	const ImGuiTreeNodeFlags BASE_FLAGS = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick; // XXX | ImGuiTreeNodeFlags_Selected;

	if (childrenCount == 0)
	{
		if (ImGui::Selectable(name, entity == this->selectedEntity, ImGuiSelectableFlags_SpanAllColumns))
		{
			this->selectedEntity = entity;
			MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
			EntitySelectionMessage message(entity);
			messagesManager->notify(&message);
		}
	}
	else
	{
		ImGuiTreeNodeFlags flags = BASE_FLAGS;
		if (entity == this->selectedEntity)
			flags |= ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_Selected;

		bool open = ImGui::TreeNodeEx(reinterpret_cast<void*>(entity), flags, name);

		if (ImGui::IsItemClicked())
		{
			this->selectedEntity = entity;
			MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
			EntitySelectionMessage message{ entity };
			messagesManager->notify(&message);
		}

		if (open)
		{
			for (uint32_t i = 0; i < childrenCount; i++)
			{
				drawEntityTree(entity->getChild(i), i);
			}
			ImGui::TreePop();
		}
	}
}

} // namespace

#endif
