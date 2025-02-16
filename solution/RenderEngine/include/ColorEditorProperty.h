#pragma once

#include "AEditorProperty.h"
#include <glm/vec3.hpp>

namespace sre
{

class ColorEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	float* value;
	bool hasAlpha;

public:
	SRE_API ColorEditorProperty(const char* arg_title, glm::vec3& arg_value);
	SRE_API ColorEditorProperty(const char* arg_title, glm::vec4& arg_value);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
