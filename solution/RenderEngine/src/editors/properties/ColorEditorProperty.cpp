#include "ColorEditorProperty.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{
ColorEditorProperty::ColorEditorProperty(const char* arg_title, glm::vec3& arg_values)
	: AEditorProperty(arg_title), hasAlpha(false)
{
	this->values = glm::value_ptr(arg_values);
}

ColorEditorProperty::ColorEditorProperty(const char* arg_title, glm::vec4& arg_values)
	: AEditorProperty(arg_title), hasAlpha(true)
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

	if (hasAlpha)
		ImGui::ColorEdit4("##id", this->values, ImGuiColorEditFlags_NoInputs);
	else
		ImGui::ColorEdit3("##id", this->values, ImGuiColorEditFlags_NoInputs);

	ImGui::Columns(1);

	ImGui::PopID();
}

void ColorEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	propertyNode.append_child() << this->values[0];
	propertyNode.append_child() << this->values[1];
	propertyNode.append_child() << this->values[2];

	if (this->hasAlpha)
	{
		propertyNode.append_child() << this->values[3];
	}
}

void ColorEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	for (size_t i = 0; i < propertyNode.num_children(); ++i)
	{
		propertyNode[i] >> this->values[i];
	}
}

} // namespace
