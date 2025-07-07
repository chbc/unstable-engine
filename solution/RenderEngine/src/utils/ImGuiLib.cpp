#include "ImGuiLib.h"

#include "imgui/imgui.h"

namespace sre
{

namespace ImGuiLib
{

void begin(const char* title)
{
	ImGui::Begin(title);
}

void text(const char* format, const char* text)
{
	ImGui::Text(format, text);
}

void image(uint64_t textureId, float width, float height)
{
	ImGui::Image(textureId, ImVec2{ width, height });
}

bool button(const char* label, float width, float height)
{
	return ImGui::Button(label, ImVec2{ width, height });
}

bool imageButton(const char* id, uint64_t textureId, float width, float height)
{
	return ImGui::ImageButton(id, textureId, ImVec2{ width, height });
}

void setNextItemAllowOverlap()
{
	ImGui::SetNextItemAllowOverlap();
}

bool selectable(const char* label, bool selected)
{
	return ImGui::Selectable(label, selected);
}

void sameLine()
{
	ImGui::SameLine();
}

void separatorText(const char* label)
{
	ImGui::SeparatorText(label);
}

void end()
{
	ImGui::End();
}

} // namespace

} // namespace
