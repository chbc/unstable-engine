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
		ImGui::CollapsingHeader("Properties") &&
		ImGui::TreeNode("Transform")
	)
	{
		ImGui::Columns(2);
		ImGui::Separator();

		glm::vec3 p = this->entity->getTransform()->getPosition();
		float position[3] = { p.x, p.y, p.z };
		float rotation[3] = { 0.0f, 0.0f, 0.0f };
		float scale[3] = { 1.0f, 1.0f, 1.0f };

		ImGui::Text("Position");
		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		ImGui::DragFloat3("##position", position, 0.1f, 0, 0, "%.1f");

		ImGui::NextColumn();
		ImGui::Text("Rotation");
		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		ImGui::DragFloat3("##rotation", rotation, 0.1f, -360, 360, "%.1f");

		ImGui::NextColumn();
		ImGui::Text("Scale");
		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		ImGui::DragFloat3("##scale", scale, 0.1f, 0, 0, "%.1f");

		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::TreePop();
	}
	ImGui::End();
}

void EditorEntityProperties::onEntitySelected(void* data)
{
	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);
	this->entity = message->entity;
}

} // namespace

#endif
