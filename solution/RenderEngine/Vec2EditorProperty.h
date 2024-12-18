#pragma once

#include "AEditorProperty.h"
#include <glm/vec2.hpp>

namespace sre
{

class Vec2EditorProperty : public AEditorProperty
{
private:
	glm::vec2* values;
	float defaultValue;

public:
	Vec2EditorProperty(const char* arg_title, glm::vec2* arg_values, float arg_defaultValue = 0.0f);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
