#include "MeshEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "Mesh.h"

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui/imgui.h"
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

MeshEditorProperty::MeshEditorProperty(const char* title, Mesh** arg_value)
	: AEditorProperty(title), value(arg_value)
{ }

void MeshEditorProperty::onDraw()
{
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text((*this->value)->filePath.c_str());
}

void MeshEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << (*this->value)->filePath;
}

void MeshEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	std::string filePath;
	propertyNode >> filePath;

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*this->value = assetsManager->loadMesh(filePath.c_str());
}

void MeshEditorProperty::copy(AEditorProperty* destination)
{
	MeshEditorProperty* derivedProperty = static_cast<MeshEditorProperty*>(destination);

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*derivedProperty->value = assetsManager->loadMesh((*this->value)->filePath.c_str());
}

} // namespace
