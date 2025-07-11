#include "StringEditorProperty.h"

#include "imgui/imgui.h"
#include "rapidyaml/rapidyaml.hpp"

namespace sre
{

StringEditorProperty::StringEditorProperty(const char* title, const std::string& arg_text)
	: AEditorProperty(title), text(arg_text)
{ }

void StringEditorProperty::onDraw()
{
	ImGui::Text(this->text.c_str());
}

void StringEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << this->text;
}

void StringEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode >> this->text;
}

void StringEditorProperty::copy(AEditorProperty* destination)
{
	StringEditorProperty* derivedProperty = static_cast<StringEditorProperty*>(destination);
	derivedProperty->text = this->text;
}

} // namespace
