#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorMenuBar.h"
#include "EngineValues.h"
#include "MessagesManager.h"
#include "SingletonsManager.h"
#include "EditorMessages.h"

#include "imgui/imgui.h"
#include "SceneLoader.h"

namespace sre
{

EditorMenuBar::EditorMenuBar(bool* demoEnabled) 
	: isDemoEnabled(demoEnabled) { }

void EditorMenuBar::onEditorGUI()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New scene");
			if (ImGui::MenuItem("Open scene"))
			{
				SceneLoader::load(nullptr);
			}

			ImGui::MenuItem("Save scene");
			ImGui::MenuItem("Save scene as");
			if (ImGui::MenuItem("Exit"))
				this->exitEditor();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Preferences");
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

	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape), false))
		exitEditor();
}

void EditorMenuBar::exitEditor()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
	ExitEditorMessage message;
	messagesManager->notify(&message);
}

} // namespace

#endif
