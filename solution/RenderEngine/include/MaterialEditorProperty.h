#pragma once

#include "AEditorProperty.h"

namespace sre
{

class Material;

class MaterialEditorProperty : public AEditorProperty
{
private:
	std::string fileName;
	Material* material;

public:
	MaterialEditorProperty(const char* title, Material* arg_material);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
