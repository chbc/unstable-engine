#include "MeshEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "MeshData.h"

// XXX MOVER IMGUI PRA UM WRAPPER
#include "imgui.h"
#include "rapidyaml.hpp"

#include <sstream>

namespace sre
{

MeshEditorProperty::MeshEditorProperty(const char* title, MeshData** arg_value, std::string* arg_modelPath)
	: AEditorProperty(title), value(arg_value), modelPath(arg_modelPath)
{ }

void MeshEditorProperty::onDraw()
{
	std::stringstream ss;
	ss << *this->modelPath << " (" << (*this->value)->name << ")";
	ImGui::Text(ss.str().c_str());
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
	derivedProperty->modelPath = this->modelPath;
}

} // namespace
