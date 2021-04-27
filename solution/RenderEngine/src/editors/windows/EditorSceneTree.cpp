#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorSceneTree.h"
#include "SceneManager.h"

#include "imgui/imgui.h"

namespace sre
{

EditorSceneTree::EditorSceneTree(SceneManager* arg_sceneManager) : sceneManager(arg_sceneManager)
{ }

void EditorSceneTree::onEditorGUI()
{
	ImGui::SetNextWindowPos(ImVec2(854.0f, 19.0f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(170.0f, 375.0f), ImGuiCond_Once);

	ImGui::Begin("Scene Tree");

	if (ImGui::TreeNodeEx("scene_name", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int index = 0;
		for (const auto& item : this->sceneManager->entities)
		{
			if (item.second->getChildrenCount() == 0)
				ImGui::TreeNodeEx("entity", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, item.first.c_str());
			else if (ImGui::TreeNode(reinterpret_cast<void*>(static_cast<intptr_t>(index)), item.first.c_str()))
			{
				this->drawEntityTree(item.second.get(), index);
				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}

	ImGui::End();
}

void EditorSceneTree::drawEntityTree(Entity* entity, int index) const
{
	const char* name = entity->getName();
	const uint32_t childrenCount = entity->getChildrenCount();

	if (childrenCount == 0)
	{
		ImGui::TreeNodeEx("entity", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, name);
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
