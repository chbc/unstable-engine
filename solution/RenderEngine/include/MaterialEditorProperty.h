#pragma once

#include "AEditorProperty.h"

namespace sre
{

class MaterialEditorProperty : public AEditorProperty
{
private:
	class Material* material;

public:
	MaterialEditorProperty(const char* title, class Material* arg_material);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;

};

} // namespace
