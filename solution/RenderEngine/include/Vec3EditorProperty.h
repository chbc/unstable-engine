#pragma once

#include "AEditorProperty.h"
#include <glm/vec3.hpp>

namespace sre
{

class Vec3EditorProperty : public AEditorProperty
{
private:
	glm::vec3* values;
	float defaultValue;

public:
	SRE_API Vec3EditorProperty(const char* arg_title, glm::vec3* arg_values, float arg_defaultValue = 0.0f);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
