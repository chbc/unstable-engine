#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorEntityProperties.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"

#include "imgui/imgui.h"

namespace sre
{

bool yeah = false;	// XXX

void EditorEntityProperties::onEditorGUI()
{
	ImGui::SetNextWindowPos(ImVec2(854.0f, 394.0f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(170.0f, 374.0f), ImGuiCond_Once);

	ImGui::Begin("Properties");

	if (ImGui::TreeNode("Transform"))
	{
		ImGui::Columns(2);
		ImGui::Separator();

		static float position[3] = { 0.0f, 0.0f, 0.0f };
		static float rotation[3] = { 0.0f, 0.0f, 0.0f };
		static float scale[3] = { 1.0f, 1.0f, 1.0f };

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

		// ### TESTE DE NOTIFICAÇÃO
		if (!yeah)
		{
			MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
			UPTR<XXX_Message> message = make_unique<XXX_Message>();
			message->a = 15;
			messagesManager->notify(message.get());

			yeah = true;
		}
	}
	ImGui::End();
}

} // namespace

#endif
