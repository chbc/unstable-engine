#include "Mat4EditorProperty.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

Mat4EditorProperty::Mat4EditorProperty(const char* arg_title, glm::mat4* arg_values)
	: AEditorProperty(arg_title)
{
	this->values = arg_values;
}

void Mat4EditorProperty::draw()
{
	float* matrix = glm::value_ptr(*this->values);

	this->drawXYZ("Position", &matrix[12], &matrix[13], &matrix[14]);
	this->drawXYZ("Scale", &matrix[0], &matrix[5], &matrix[10]);
}

void Mat4EditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;

	const float* valuesArray = glm::value_ptr(*this->values);
	for (int i = 0; i < 16; ++i)
		propertyNode.append_child() << valuesArray[i];
}

void Mat4EditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	float* valuesArray = glm::value_ptr(*this->values);
	for (int i = 0; i < 16; ++i)
		propertyNode[i] >> valuesArray[i];
}

void Mat4EditorProperty::drawXYZ(const char* itemTitle, float* x, float* y, float* z)
{
	ImGui::PushID(itemTitle);

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(itemTitle);
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	if (ImGui::Button("X", buttonSize))
		*x = 0.0f;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", x, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	if (ImGui::Button("Y", buttonSize))
		*y = 0.0f;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	if (ImGui::Button("Z", buttonSize))
		*z = 0.0f;
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();
	ImGui::Columns(1);

	ImGui::PopID();
}

} // namespace
