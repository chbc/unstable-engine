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
		this->drawFileGroup();
		this->drawEditGroup();
		this->drawEntitiesGroup();
		this->drawHelpGroup();

		ImGui::EndMenuBar();
	}

	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape), false) ||
		ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Home), false)
	)
	{
		exitEditor();
	}
}

void EditorMenuBar::drawFileGroup()
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
}

void EditorMenuBar::drawEditGroup()
{
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::MenuItem("Preferences");
		ImGui::EndMenu();
	}
}

void EditorMenuBar::drawEntitiesGroup()
{
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

			if (ImGui::MenuItem("Sphere"))
			{
				this->controller->createSphere();
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
}

void EditorMenuBar::drawHelpGroup()
{
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("ImGui Demo"))
			*this->isDemoEnabled = true;

		ImGui::MenuItem("About");
		ImGui::EndMenu();
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
