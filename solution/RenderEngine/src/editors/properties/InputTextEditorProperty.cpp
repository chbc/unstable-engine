#include "InputTextEditorProperty.h"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "RYMLLib.h"

#include "Log.h"

namespace sre
{

InputTextEditorProperty::InputTextEditorProperty(const char* title, std::string* arg_text)
	: AEditorProperty(title), text(arg_text)
{ }

void InputTextEditorProperty::onDraw()
{
	if (ImGui::InputText("", this->text))
	{
		this->onPropertyChanged();
	}
}

void InputTextEditorProperty::onSerialize(c4::yml::NodeRef propertyNode)
{
	propertyNode |= ryml::MAP;
	propertyNode["Text"] << RYMLLib::toC4Substr(*this->text);
}

void InputTextEditorProperty::onDeserialize(c4::yml::ConstNodeRef propertyNode)
{
	RYMLLib::readString(propertyNode["Text"], *this->text);
}

void InputTextEditorProperty::copy(AEditorProperty* destination)
{
	InputTextEditorProperty* derivedProperty = static_cast<InputTextEditorProperty*>(destination);
	*derivedProperty->text = *this->text;
}

} // namespace
