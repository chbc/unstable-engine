#include "Vec2EditorProperty.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_internal.h"
#include "rapidyaml.hpp"

namespace sre
{

Vec2EditorProperty::Vec2EditorProperty(const char* arg_title, glm::vec2* arg_value, float arg_defaultValue)
	: AEditorProperty(arg_title), value(arg_value), defaultValue(arg_defaultValue)
{ }

void Vec2EditorProperty::onDraw()
{
	bool valueChanged = false;

	ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	if (ImGui::Button("X", buttonSize))
	{
		this->value->x = this->defaultValue;
		valueChanged = true;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##X", &this->value->x, 0.1f, 0.0f, 0.0f, "%.3f"))
	{
		valueChanged = true;
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	if (ImGui::Button("Y", buttonSize))
	{
		this->value->y = this->defaultValue;
		valueChanged = true;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &this->value->y, 0.1f, 0.0f, 0.0f, "%.3f"))
	{
		valueChanged = true;
	}
	ImGui::PopItemWidth();
	ImGui::PopStyleVar();

	if (valueChanged)
	{
		this->onPropertyChanged();
	}
}

void Vec2EditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	propertyNode.append_child() << this->value->x;
	propertyNode.append_child() << this->value->y;
}

void Vec2EditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode[0] >> this->value->x;
	propertyNode[1] >> this->value->y;
}

void Vec2EditorProperty::copy(AEditorProperty* destination)
{
	Vec2EditorProperty* derivedProperty = static_cast<Vec2EditorProperty*>(destination);
	*derivedProperty->value = *this->value;
	derivedProperty->defaultValue = this->defaultValue;
}

} // namespace
