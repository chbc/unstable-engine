#pragma once

#include "AEditorProperty.h"
#include <glm/vec3.hpp>

namespace sre
{

class XYZEditorProperty : public AEditorProperty
{
private:
	float* values[3];

public:
	XYZEditorProperty(const char* arg_title, glm::vec3& arg_values);
	XYZEditorProperty(const char* arg_title, float* arg_values);
	XYZEditorProperty(const char* arg_title, float* x, float* y, float* z);

	void draw() override;
};

} // namespace
