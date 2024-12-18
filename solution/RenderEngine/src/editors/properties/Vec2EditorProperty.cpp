#include "Vec2EditorProperty.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

Vec2EditorProperty::Vec2EditorProperty(const char* arg_title, glm::vec2* arg_values, float arg_defaultValue)
	: AEditorProperty(arg_title), values(arg_values), defaultValue(arg_defaultValue)
{ }

void Vec2EditorProperty::draw()
{
	bool valueChanged = false;

	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	if (ImGui::Button("X", buttonSize))
	{
		this->values->x = this->defaultValue;
		valueChanged = true;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##X", &this->values->x, 0.1f, 0.0f, 0.0f, "%.2f"))
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
		this->values->y = this->defaultValue;
		valueChanged = true;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &this->values->y, 0.1f, 0.0f, 0.0f, "%.2f"))
	{
		valueChanged = true;
	}
	ImGui::PopItemWidth();
	ImGui::PopStyleVar();
	ImGui::Columns(1);

	ImGui::PopID();

	if (valueChanged && (this->onValueChanged != nullptr))
	{
		this->onValueChanged();
	}
}

void Vec2EditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	propertyNode.append_child() << this->values->x;
	propertyNode.append_child() << this->values->y;
}

void Vec2EditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode[0] >> this->values->x;
	propertyNode[1] >> this->values->y;

	if (this->onValueChanged != nullptr)
	{
		this->onValueChanged();
	}
}

} // namespace
