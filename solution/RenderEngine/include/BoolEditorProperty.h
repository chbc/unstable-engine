#pragma once

#include "AEditorProperty.h"

namespace sre
{

class BoolEditorProperty : public AEditorProperty
{

private:
	bool* value;

public:
	BoolEditorProperty(const char* title, bool* arg_value);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
