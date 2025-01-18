#pragma once

#include "AEditorProperty.h"

namespace sre
{

class FloatEditorProperty : public AEditorProperty
{

private:
	float* value;

public:
	SRE_API FloatEditorProperty(const char* title, float* arg_value);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
