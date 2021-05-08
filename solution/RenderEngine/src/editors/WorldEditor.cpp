#if defined(DEBUG) && !defined(__ANDROID__)

#include "WorldEditor.h"
#include "EditorMenuBar.h"
#include "EditorSceneTree.h"
#include "EditorEntityProperties.h"
#include "imgui/imgui.h"

namespace sre
{

WorldEditor::WorldEditor(SceneManager* arg_sceneManager, bool* editorEnabled)
	: sceneManager(arg_sceneManager), showDemo(false)
{
	this->windows[0] = UPTR<IEditorWindow>(new EditorMenuBar{ editorEnabled, &this->showDemo });
	this->windows[1] = UPTR<IEditorWindow>(new EditorSceneTree{ sceneManager });
	this->windows[2] = UPTR<IEditorWindow>(new EditorEntityProperties);
}

void WorldEditor::init()
{
	for (const auto& item : this->windows)
		item->onInit();
}

void WorldEditor::onEditorGUI()
{
	if (this->showDemo)
		ImGui::ShowDemoWindow(&this->showDemo);
	else
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		for (const auto& item : this->windows)
			item->onEditorGUI();
	}
}

void WorldEditor::release()
{
	for (const auto& item : this->windows)
		item->onRelease();
}

} // namespace
#endif
