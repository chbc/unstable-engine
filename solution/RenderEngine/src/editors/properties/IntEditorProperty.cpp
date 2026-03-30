#include "IntEditorProperty.h"

#include <sstream>

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui.h"
#include "rapidyaml.hpp"

namespace sre
{

IMPLEMENT_PROPERTY(IntEditorProperty)

IntEditorProperty::IntEditorProperty(const char* title, int* arg_value)
	: AEditorProperty(title), value(arg_value)
{ }

void IntEditorProperty::onDraw()
{
	if (ImGui::DragInt("##id", this->value))
	{
		this->onPropertyChanged();
	}
}

void IntEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << *value;
}

void IntEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode >> *value;
}

} // namespace
