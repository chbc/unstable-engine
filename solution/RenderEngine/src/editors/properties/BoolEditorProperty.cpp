#include "BoolEditorProperty.h"

#include <sstream>

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui.h"
#include "rapidyaml.hpp"

namespace sre
{

IMPLEMENT_PROPERTY(BoolEditorProperty)

BoolEditorProperty::BoolEditorProperty(const char* title, bool* arg_value)
	: AEditorProperty(title), value(arg_value)
{ }

void BoolEditorProperty::onDraw()
{
	ImGui::SetColumnWidth(0, 100.0f);

	if (ImGui::Checkbox("##id", this->value))
	{
		this->onPropertyChanged();
	}
}

void BoolEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << *value;
}

void BoolEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode >> *value;
}

} // namespace
