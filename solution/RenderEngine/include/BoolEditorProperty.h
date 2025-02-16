#pragma once

#include "AEditorProperty.h"

namespace sre
{

class BoolEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	bool* value;

public:
	SRE_API BoolEditorProperty(const char* title, bool* arg_value);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
