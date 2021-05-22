#include "FloatEditorProperty.h"

#include "imgui/imgui.h"

namespace sre
{

FloatEditorProperty::FloatEditorProperty(const char* title, float* arg_values)
	: AEditorProperty(title), value(arg_values)
{ }

void FloatEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());
	ImGui::NextColumn();
	//ImGui::SetColumnWidth(0, 50.0f);

	ImGui::DragFloat("##id", this->value, 0.1f, 0.0f, 0.0f, "%.2f");

	ImGui::Columns(1);

	ImGui::PopID();
}

} // namespace
