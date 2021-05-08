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

	if (ImGui::CollapsingHeader("Scene Tree", ImGuiTreeNodeFlags_DefaultOpen) && ImGui::TreeNodeEx("scene_name", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int index = 0;
		for (const auto& item : this->sceneManager->entities)
			this->drawEntityTree(item.second.get(), index);

		ImGui::TreePop();
	}
}

void EditorSceneTree::drawEntityTree(Entity* entity, int index)
{
	const char* name = entity->getName();
	const uint32_t childrenCount = entity->getChildrenCount();

	if (childrenCount == 0)
	{
		if (ImGui::Selectable(name, entity == this->selectedEntity))
		{
			this->selectedEntity = entity;
			MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
			EntitySelectionMessage message(entity);
			messagesManager->notify(&message);
		}
	}
	else if (ImGui::TreeNode(reinterpret_cast<void*>(static_cast<intptr_t>(index)), name))
	{
		for (int i = 0; i < childrenCount; i++)
		{
			drawEntityTree(entity->getChild(i), i);
		}
		ImGui::TreePop();
	}
}

} // namespace

#endif
