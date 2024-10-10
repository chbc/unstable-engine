#include "MeshEditorProperty.h"

#include "SingletonsManager.h"
#include "AssetsManager.h"

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
	propertyNode << "../../media/Cube.mesh";
}

void MeshEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	std::string fileName;
	propertyNode >> fileName;

	AssetsManager* assetsManager = SingletonsManager::getInstance()->resolve<AssetsManager>();

	MeshData* meshData = assetsManager->loadMesh(fileName.c_str());
	this->meshData->reset(meshData);
}

} // namespace
