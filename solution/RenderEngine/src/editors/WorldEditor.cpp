#if !defined(RELEASE) && !defined(__ANDROID__)

#include "WorldEditor.h"
#include "EditorMenuBar.h"
#include "EditorSceneTree.h"
#include "EditorEntityProperties.h"
#include "EditorSceneViewport.h"
#include "EditorFileBrowser.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "EditorMessages.h"
#include "MessagesManager.h"

#include "imgui/imgui.h"

namespace sre
{

WorldEditor::WorldEditor(ScenesManager* arg_scenesManager)
	: scenesManager(arg_scenesManager), showDemo(false), wasShowingDemo(false)
{
    this->controller = UPTR<EditorsController>(new EditorsController{ this->scenesManager });
	this->menuBar = UPTR<IEditorWindow>(new EditorMenuBar{ &this->showDemo, this->controller.get() });
	this->windows[0] = UPTR<IEditorWindow>(new EditorSceneTree{ scenesManager, this->controller.get() });
	this->windows[1] = UPTR<IEditorWindow>(new EditorEntityProperties);
    this->windows[2] = UPTR<IEditorWindow>(new EditorSceneViewport{ this->controller.get()});
    this->windows[3] = UPTR<IEditorWindow>(new EditorFileBrowser{ this->controller.get() });
    
    this->showPopupAction = SPTR<Action>(new Action([&](void* message) { this->onShowPopup(message); }));
}

void WorldEditor::init()
{
    this->menuBar->onInit();
	for (const auto& item : this->windows)
		item->onInit();

    this->currentPopup.reset();

    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->addListener<ShowPopupEditorMessage>(this->showPopupAction.get());

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void WorldEditor::onUpdate(float elapsedTime)
{
    for (const auto& item : this->windows)
        item->onUpdate(elapsedTime);
}

bool WorldEditor::onEditorGUI()
{
    if (this->showDemo)
    {
        if (!this->wasShowingDemo)
        {
            this->wasShowingDemo = true;
            SingletonsManager* singletonsManager = SingletonsManager::getInstance();
            singletonsManager->get<RenderManager>()->setTargetFBO(0);
        }

        ImGui::ShowDemoWindow(&this->showDemo);
        return false;
    }
    
    if (this->wasShowingDemo)
    {
        this->wasShowingDemo = false;
        SingletonsManager* singletonsManager = SingletonsManager::getInstance();
        singletonsManager->get<RenderManager>()->setTargetFBO(EditorSceneViewport::Fbo);
    }

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    static bool openDockspace = true;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpace Demo", &openDockspace, window_flags);
    ImGui::PopStyleVar();

    ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    // ------------- //
    this->menuBar->onEditorGUI();

    for (const auto& item : this->windows)
        item->onEditorGUI();

    if (this->currentPopup && this->currentPopup->isOpen())
    {
        this->currentPopup->onEditorGUI();
    }
    // ------------- //

    return true;
}

void WorldEditor::onGUIEnd()
{
    ImGui::End();
}

void WorldEditor::onShowPopup(void* message)
{
    ShowPopupEditorMessage* popupMessage = static_cast<ShowPopupEditorMessage*>(message);
    this->currentPopup.reset(popupMessage->popup);
}

void WorldEditor::cleanUp()
{
    if (this->currentPopup)
    {
        this->currentPopup->close(false);
    }

    this->menuBar->onCleanUp();
    for (const auto& item : this->windows)
    {
        item->onCleanUp();
    }

    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->removeListener<ShowPopupEditorMessage>(this->showPopupAction.get());
}

void WorldEditor::release()
{
    this->showDemo = false;
    this->wasShowingDemo = false;

	for (const auto& item : this->windows)
		item->onRelease();
}

} // namespace
#endif
