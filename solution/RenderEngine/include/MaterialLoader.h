#pragma once

#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

class Material;
class AMaterialComponent;

class MaterialLoader
{
public:
	void save(Material* material, const char* filePath);
	Material* load(const char* filePath);

private:
	void serializeComponent(c4::yml::NodeRef& componentNode, AMaterialComponent* component);
	void deserializeComponent(c4::yml::ConstNodeRef& componentNode, Material* material);
};

} // namespace
