#pragma once

#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

class Material;
class AMaterialComponent;

class MaterialLoader
{
public:
	void save(Material* material, const char* name);
	Material* load(const char* fileName);

private:
	void serializeComponent(c4::yml::NodeRef& componentNode, AMaterialComponent* component);
	void deserializeComponent(c4::yml::ConstNodeRef& componentNode, Material* material);
};

} // namespace
