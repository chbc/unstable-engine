#include "MeshEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "MeshData.h"

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui/imgui.h"
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

MeshEditorProperty::MeshEditorProperty(const char* title, MeshData** arg_value, std::string* arg_modelPath)
	: AEditorProperty(title), value(arg_value), modelPath(arg_modelPath)
{ }

void MeshEditorProperty::onDraw()
{
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->modelPath->c_str());
	ImGui::Text((*this->value)->name.c_str());
}

void MeshEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= ryml::MAP;
	propertyNode["FilePath"] << *this->modelPath;
	propertyNode["MeshName"] << (*this->value)->name;
}

void MeshEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	std::string filePath;
	std::string meshName;

	propertyNode["FilePath"] >> filePath;
	propertyNode["MeshName"] >> meshName;

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*this->value = assetsManager->loadMesh(filePath.c_str(), meshName.c_str());
	*this->modelPath = filePath;
}

void MeshEditorProperty::copy(AEditorProperty* destination)
{
	MeshEditorProperty* derivedProperty = static_cast<MeshEditorProperty*>(destination);

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*derivedProperty->value = assetsManager->loadMesh(this->modelPath->c_str(), (*this->value)->name.c_str());
}

} // namespace
