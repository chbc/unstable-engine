#pragma once

#include "AEditorProperty.h"
#include <glm/gtc/type_ptr.hpp>

namespace sre
{

class Mat4EditorProperty : public AEditorProperty
{
private:
	glm::mat4* values;

public:
	Mat4EditorProperty(const char* arg_title, glm::mat4* arg_values);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;

private:
	void drawXYZ(const char* itemTitle, float* x, float* y, float* z);
};

} // namespace
