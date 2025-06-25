#include "InputTextEditorProperty.h"

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"
#include "rapidyaml/rapidyaml.hpp"

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

void InputTextEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= ryml::MAP;
	propertyNode["Text"] << *this->text;
}

void InputTextEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode["FilePath"] >> *this->text;
}

void InputTextEditorProperty::copy(AEditorProperty* destination)
{
	InputTextEditorProperty* derivedProperty = static_cast<InputTextEditorProperty*>(destination);
	*derivedProperty->text = *this->text;
}

} // namespace
