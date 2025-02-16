#include "ColorEditorProperty.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{
ColorEditorProperty::ColorEditorProperty(const char* arg_title, glm::vec3& arg_value)
	: AEditorProperty(arg_title), hasAlpha(false)
{
	this->value = glm::value_ptr(arg_value);
}

ColorEditorProperty::ColorEditorProperty(const char* arg_title, glm::vec4& arg_value)
	: AEditorProperty(arg_title), hasAlpha(true)
{
	this->value = glm::value_ptr(arg_value);
}

void ColorEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());
	ImGui::NextColumn();

	bool valueChanged = false;
	if (hasAlpha)
	{
		valueChanged = ImGui::ColorEdit4("##id", this->value, ImGuiColorEditFlags_NoInputs);
	}
	else
	{
		valueChanged = ImGui::ColorEdit3("##id", this->value, ImGuiColorEditFlags_NoInputs);
	}

	if (valueChanged)
	{
		this->onValueChanged();
	}

	ImGui::Columns(1);

	ImGui::PopID();
}

void ColorEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	propertyNode.append_child() << this->value[0];
	propertyNode.append_child() << this->value[1];
	propertyNode.append_child() << this->value[2];

	if (this->hasAlpha)
	{
		propertyNode.append_child() << this->value[3];
	}
}

void ColorEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	for (size_t i = 0; i < propertyNode.num_children(); ++i)
	{
		propertyNode[i] >> this->value[i];
	}
}

void ColorEditorProperty::copy(AEditorProperty* destination)
{
	ColorEditorProperty* derivedProperty = static_cast<ColorEditorProperty*>(destination);
	derivedProperty->value[0] = this->value[0];
	derivedProperty->value[1] = this->value[1];
	derivedProperty->value[2] = this->value[2];

	derivedProperty->hasAlpha = this->hasAlpha;
	if (this->hasAlpha)
	{
		derivedProperty->value[3] = this->value[3];
	}
}

} // namespace
