#include "FloatEditorProperty.h"

#include <sstream>

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui.h"
#include "rapidyaml.hpp"

namespace sre
{

IMPLEMENT_PROPERTY(FloatEditorProperty)

FloatEditorProperty::FloatEditorProperty(const char* title, float* arg_values)
	: AEditorProperty(title), value(arg_values)
{ }

void FloatEditorProperty::onDraw()
{
	ImGui::SetColumnWidth(0, 100.0f);

	if (ImGui::DragFloat("##id", this->value, 0.1f, 0.0f, 0.0f, "%.2f"))
	{
		this->onPropertyChanged();
	}
}

void FloatEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << *value;
}

void FloatEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode >> *value;
}

} // namespace
