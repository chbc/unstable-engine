#include "TextureEditorProperty.h"

#include "imgui/imgui.h"

namespace sre
{

TextureEditorProperty::TextureEditorProperty(const char* title, uint32_t arg_value)
	: AEditorProperty(title)
{
	this->value = reinterpret_cast<void*>(arg_value);
}

void TextureEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());
	ImGui::NextColumn();
	ImGui::SetColumnWidth(0, 100.0f);

	ImGui::Image(this->value, ImVec2{ 64.0f, 64.0f}, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });

	ImGui::Columns(1);

	ImGui::PopID();
}

} // namespace
