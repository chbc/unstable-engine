#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorMenuBar.h"
#include "EngineValues.h"
#include "MessagesManager.h"
#include "SingletonsManager.h"
#include "EditorMessages.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "RenderEngine.h"
#include "SceneLoader.h"

#include "imgui/imgui.h"

namespace sre
{

EditorMenuBar::EditorMenuBar(bool* demoEnabled, ScenesManager* arg_scenesManager)
	: isDemoEnabled(demoEnabled), scenesManager(arg_scenesManager)
{
	/* XXX
	Scene* scene = this->scenesManager->createScene("new_scene");
	SceneLoader::load(scene);

	this->scenesManager->onScenesLoaded();
	SingletonsManager::getInstance()->get<RenderManager>()->onSceneLoaded();
	*/
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
				RenderEngine::getInstance()->loadScene("../../scenes/test.scene");
			}

			if (ImGui::MenuItem("Save scene"))
			{
				SceneLoader::save(this->scenesManager->runtimeScene.get());
			}

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

	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape), false) ||
		ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Home), false)
	)
	{
		exitEditor();
	}
}

void EditorMenuBar::exitEditor()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
	ExitEditorMessage message;
	messagesManager->notify(&message);
}

} // namespace

#endif
