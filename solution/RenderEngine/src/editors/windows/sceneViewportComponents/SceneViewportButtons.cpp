#include "SceneViewportButtons.h"
#include "Texture.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "AGraphicsWrapper.h"
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
    if (ImGui::Begin("Viewport buttons", &open, window_flags))
    {
		this->drawOrientationItem();
	    ImGui::SameLine();
		this->drawBackfaceCullingItem();
		ImGui::SameLine();
        this->drawGridItem();
    }

    ImGui::End();
}

void SceneViewportButtons::drawOrientationItem()
{
    ImGui::SetNextItemWidth(70);
    if (ImGui::Combo("##Orientation", &this->currentOrientationItem, this->orientationComboItems, 2))
    {
        this->notifyOrientationChanged();
    }

    if (ImGui::IsItemHovered())
    {
        ImGui::SetTooltip("Change orientation mode (Local/Global)");
    }
}

void SceneViewportButtons::drawBackfaceCullingItem()
{
    if (ImGui::Button("Backface Culling")) //, &this->backfaceCullingEnabled))
    {
		this->backfaceCullingEnabled = !this->backfaceCullingEnabled;
        this->refreshBackfaceCulling();
    }

    if (ImGui::IsItemHovered())
    {
        ImGui::SetTooltip("Toggle backface culling");
    }
}

void SceneViewportButtons::drawGridItem()
{
    if (ImGui::Button("Grid"))
    {
		this->gridEnabled = !this->gridEnabled;
		this->notifyGridEnabledChanged();
    }

    if (ImGui::IsItemHovered())
    {
        ImGui::SetTooltip("Toggle grid");
    }
}

void SceneViewportButtons::notifyOrientationChanged()
{
    ChangeGuizmoModeMessage message{ this->currentOrientationItem };
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->notify(&message);
}

void SceneViewportButtons::notifyGridEnabledChanged()
{
    SetGridEnabledEditorMessage message{ this->gridEnabled };
    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->notify(&message);
}

void SceneViewportButtons::refreshBackfaceCulling()
{
	AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
	graphicsWrapper->enableBackfaceCulling(this->backfaceCullingEnabled);
}

} // namespace
