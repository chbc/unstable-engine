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

void sameLine()
{
	ImGui::SameLine();
}

void end()
{
	ImGui::End();
}

} // namespace

} // namespace
