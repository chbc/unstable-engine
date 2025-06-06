#include "Vec3EditorProperty.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_internal.h"
#include "rapidyaml.hpp"

namespace sre
{

Vec3EditorProperty::Vec3EditorProperty(const char* arg_title, glm::vec3* arg_value, float arg_defaultValue)
	: AEditorProperty(arg_title), value(arg_value), defaultValue(arg_defaultValue)
{ }

void Vec3EditorProperty::onDraw()
{
	bool valueChanged = false;

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
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
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	if (ImGui::Button("Z", buttonSize))
	{
		this->value->z = this->defaultValue;
		valueChanged = true;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##Z", &this->value->z, 0.1f, 0.0f, 0.0f, "%.3f"))
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

void Vec3EditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	propertyNode.append_child() << this->value->x;
	propertyNode.append_child() << this->value->y;
	propertyNode.append_child() << this->value->z;
}

void Vec3EditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode[0] >> this->value->x;
	propertyNode[1] >> this->value->y;
	propertyNode[2] >> this->value->z;
}

void Vec3EditorProperty::copy(AEditorProperty* destination)
{
	Vec3EditorProperty* derivedProperty = static_cast<Vec3EditorProperty*>(destination);
	*derivedProperty->value = *this->value;
	derivedProperty->defaultValue = this->defaultValue;
}

} // namespace
