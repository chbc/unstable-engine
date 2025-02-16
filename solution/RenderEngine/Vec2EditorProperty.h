#pragma once

#include "AEditorProperty.h"
#include <glm/vec2.hpp>

namespace sre
{

class Vec2EditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	glm::vec2* value;
	float defaultValue;

public:
	SRE_API Vec2EditorProperty(const char* arg_title, glm::vec2* arg_value, float arg_defaultValue = 0.0f);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
