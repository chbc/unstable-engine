#include "ColorEditorProperty.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

namespace sre
{
ColorEditorProperty::ColorEditorProperty(const char* arg_title, glm::vec3& arg_values)
	: AEditorProperty(arg_title)
{
	this->values = glm::value_ptr(arg_values);
}

void ColorEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());
	ImGui::NextColumn();

	ImGui::ColorEdit3("##id", this->values);

	ImGui::Columns(1);

	ImGui::PopID();
}

} // namespace
