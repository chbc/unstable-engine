#if defined(DEBUG) && !defined(__ANDROID__)

#include "WorldEditor.h"
#include "SingletonsManager.h"
#include "EditorMenuBar.h"
#include "EditorSceneTree.h"
#include "EditorEntityProperties.h"
#include "MessagesManager.h"
#include "EditorMessages.h"

#include "imgui/imgui.h"

namespace sre
{

void WorldEditor::init(SceneManager* sceneManager, bool* editorEnabled)
{
	this->sceneManager = sceneManager;
	MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();

	Action action = [&](void* message) { this->XXX_MessageMethod(message); };
	messagesManager->addListener<XXX_Message>(action);

	this->showDemo = false;

	this->windows[0] = UPTR<IEditorWindow>(new EditorMenuBar{ editorEnabled, &this->showDemo });
	this->windows[1] = UPTR<IEditorWindow>(new EditorSceneTree{ sceneManager });
	this->windows[2] = UPTR<IEditorWindow>(new EditorEntityProperties);
}

void WorldEditor::XXX_MessageMethod(void* message)
{
	XXX_Message* aMessage = static_cast<XXX_Message*>(message);
	aMessage->a = 11;
}

void WorldEditor::onEditorGUI()
{
	if (this->showDemo)
		ImGui::ShowDemoWindow(&this->showDemo);
	else
	{
		for (const auto& item : this->windows)
			item->onEditorGUI();
	}
}

} // namespace
#endif
