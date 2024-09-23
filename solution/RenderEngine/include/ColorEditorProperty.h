#pragma once

#include "AEditorProperty.h"
#include <glm/vec3.hpp>

namespace sre
{

class ColorEditorProperty : public AEditorProperty
{
private:
	float* values;
	bool hasAlpha;

public:
	ColorEditorProperty(const char* arg_title, glm::vec3& arg_values);
	ColorEditorProperty(const char* arg_title, glm::vec4& arg_values);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
