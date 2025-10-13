#pragma once

#include "rapidyaml/rapidyaml.hpp"

namespace sre
{

class ABaseMaterial;
class Material;
class CustomMaterial;
class AMaterialComponent;

class MaterialLoader
{
public:
	void save(ABaseMaterial* material, const std::string& filePath);
	ABaseMaterial* load(const std::string& filePath);

private:
	void saveComponents(Material* material, c4::yml::NodeRef& componentsNode);
	void serializeComponent(c4::yml::NodeRef& componentNode, AMaterialComponent* component);
	ABaseMaterial* loadStandardMaterial(const std::string& filePath, c4::yml::ConstNodeRef& root);
	ABaseMaterial* loadCustomMaterial(const std::string& filePath, c4::yml::ConstNodeRef& root);
	void deserializeComponent(c4::yml::ConstNodeRef& componentNode, ABaseMaterial* material);
	void deserializeCustomComponent(c4::yml::ConstNodeRef& componentNode, ABaseMaterial* material);
};

} // namespace
