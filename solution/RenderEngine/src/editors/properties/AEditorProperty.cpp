#include "AEditorProperty.h"
#include "imgui/imgui.h"

bool sre::AEditorProperty::isSaved()
{
    return this->saved;
}

void sre::AEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
    if (this->saved)
    {
        ImGui::Text(this->title.c_str());
    }
    else
    {
        ImGui::TextColored(ImColor{ 0.75f, 0.5f, 0.0f }, this->title.c_str());
    }
	ImGui::NextColumn();

    this->onDraw();

	ImGui::Columns(1);

	ImGui::PopID();
}

void sre::AEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
    this->onSerialize(propertyNode);

    this->saved = true;
    this->onValueSerializedCallback();
}

void sre::AEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
    this->onDeserialize(propertyNode);
    this->onValueDeserializedCallback();
}

void sre::AEditorProperty::onPropertyChanged()
{
    this->saved = false;
    this->onValueChangedCallback();
}
