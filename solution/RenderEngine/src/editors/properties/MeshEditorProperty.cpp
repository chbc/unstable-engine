#include "MeshEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "Mesh.h"

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui/imgui.h"
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

MeshEditorProperty::MeshEditorProperty(const char* title, Mesh** arg_mesh)
	: AEditorProperty(title), mesh(arg_mesh)
{ }

void MeshEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());

	ImGui::NextColumn();
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->fileName.c_str());

	ImGui::Columns(1);

	ImGui::PopID();
}

void MeshEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << (*this->mesh)->fileName;
}

void MeshEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode >> this->fileName;

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*this->mesh = assetsManager->loadMesh(fileName.c_str());
}

} // namespace
