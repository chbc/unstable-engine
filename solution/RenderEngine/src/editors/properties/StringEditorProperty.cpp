#include "StringEditorProperty.h"

#include "imgui.h"
#include "RYMLLib.h"

namespace sre
{

StringEditorProperty::StringEditorProperty(const std::string& title, const std::string& arg_text)
	: AEditorProperty(title), text(arg_text)
{ }

void StringEditorProperty::onDraw()
{
	ImGui::Text("%s", this->text.c_str());
}

void StringEditorProperty::onSerialize(c4::yml::NodeRef propertyNode)
{
	c4::substr textSubstr = RYMLLib::toC4Substr(this->text);
	propertyNode.val() = textSubstr;
}

void StringEditorProperty::onDeserialize(c4::yml::ConstNodeRef propertyNode)
{
	RYMLLib::readString(propertyNode, this->text);
}

void StringEditorProperty::copy(AEditorProperty* destination)
{
	StringEditorProperty* derivedProperty = static_cast<StringEditorProperty*>(destination);
	derivedProperty->text = this->text;
}

} // namespace
