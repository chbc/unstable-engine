#pragma once

#include "AEditorProperty.h"

namespace sre
{

class TextureEditorProperty : public AEditorProperty
{

private:
	void* value;

public:
	TextureEditorProperty(const char* title, uint32_t arg_value);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
