#include "FloatEditorProperty.h"

#include <sstream>

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui/imgui.h"
#include <rapidyaml/rapidyaml.hpp>


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
	ImGui::SetColumnWidth(0, 100.0f);

	ImGui::DragFloat("##id", this->value, 0.1f, 0.0f, 0.0f, "%.2f");

	ImGui::Columns(1);

	ImGui::PopID();
}

void FloatEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << *value;
}

void FloatEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode >> *value;
}

} // namespace
