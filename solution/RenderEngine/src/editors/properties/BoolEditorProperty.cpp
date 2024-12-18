#include "BoolEditorProperty.h"

#include <sstream>

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui/imgui.h"
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

BoolEditorProperty::BoolEditorProperty(const char* title, bool* arg_value)
	: AEditorProperty(title), value(arg_value)
{ }

void BoolEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());
	ImGui::NextColumn();
	ImGui::SetColumnWidth(0, 100.0f);

	if (ImGui::Checkbox("##id", this->value))
	{
		this->onValueChanged();
	}

	ImGui::Columns(1);

	ImGui::PopID();
}

void BoolEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << *value;
}

void BoolEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode >> *value;

	if (this->onValueChanged != nullptr)
	{
		this->onValueChanged();
	}
}

} // namespace
