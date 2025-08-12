#include "SceneViewportButtons.h"
#include "Texture.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"

#include <imgui/imgui.h>

namespace sre
{

void SceneViewportButtons::drawContent(const glm::vec2& windowPos, const glm::vec2& windowSize)
{
	static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | 
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | 
        ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

    static bool open{ true };
	ImVec2 position{ windowPos.x + 5.0f, windowPos.y + 5.0f };
    ImVec2 pivot{ 0.0f, 0.0f };
    
	ImGui::SetNextWindowPos(position, ImGuiCond_Always, pivot);
    ImGui::SetNextWindowBgAlpha(0.35f);
    int previousOrientationItem = this->currentOrientationItem;
    if (ImGui::Begin("Viewport buttons", &open, window_flags))
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImGui::SetNextItemWidth(70);
		ImGui::Combo("##Orientation", &this->currentOrientationItem, this->orientationComboItems, 2);
    }
    ImGui::End();

    if (previousOrientationItem != this->currentOrientationItem)
    {
        this->notifyOrientationChanged();
	}
}

void SceneViewportButtons::notifyOrientationChanged()
{
    ChangeGuizmoModeMessage message{ this->currentOrientationItem };
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->notify(&message);
}

} // namespace
