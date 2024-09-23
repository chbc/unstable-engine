#include "MeshEditorProperty.h"

#include "MeshData.h"
#include "PrimitiveMeshFactory.h"

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui/imgui.h"
#include <rapidyaml/rapidyaml.hpp>


namespace sre
{

MeshEditorProperty::MeshEditorProperty(const char* title, UPTR<AMeshData>* arg_meshData)
	: AEditorProperty(title), meshData(arg_meshData)
{ }

void MeshEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());
	ImGui::NextColumn();
	ImGui::SetColumnWidth(0, 100.0f);
	
	ImGui::Text("XXX");

	ImGui::Columns(1);

	ImGui::PopID();
}

void MeshEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << "../../media/cube.mesh";
}

void MeshEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	this->meshData->reset(PrimitiveMeshFactory().createCube(5.0f));
}

} // namespace
