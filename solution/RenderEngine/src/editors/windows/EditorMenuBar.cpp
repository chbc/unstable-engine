#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorMenuBar.h"
#include "MessagesManager.h"
#include "SingletonsManager.h"
#include "EditorMessages.h"
#include "EditorsController.h"

#include "imgui/imgui.h"

namespace sre
{

EditorMenuBar::EditorMenuBar(bool* demoEnabled, EditorsController* arg_controller)
	: isDemoEnabled(demoEnabled), controller(arg_controller)
{
}

void EditorMenuBar::onEditorGUI()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New scene");
			if (ImGui::MenuItem("Open scene"))
			{
				this->controller->loadScene();
			}

			if (ImGui::MenuItem("Save scene"))
			{
				this->controller->saveScene();
			}

			if (ImGui::MenuItem("Exit"))
				this->exitEditor();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Preferences");
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Entities"))
		{
			if (ImGui::BeginMenu("Basic Shapes"))
			{
				if (ImGui::MenuItem("Cube"))
				{
					this->controller->createCube();
				}

				if (ImGui::MenuItem("Plane"))
				{
					this->controller->createPlane();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Lights"))
			{
				if (ImGui::MenuItem("Directional Light"))
				{

				}

				if (ImGui::MenuItem("Point Light"))
				{

				}

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("ImGui Demo"))
				*this->isDemoEnabled = true;

			ImGui::MenuItem("About");
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape), false) ||
		ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Home), false)
	)
	{
		exitEditor();
	}
}

void EditorMenuBar::exitEditor()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	ExitEditorMessage message;
	messagesManager->notify(&message);
}

} // namespace

#endif
