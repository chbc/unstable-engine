#pragma once

#include "AEditorProperty.h"
#include <glm/vec3.hpp>

namespace sre
{

class ColorEditorProperty : public AEditorProperty
{
private:
	float* values;

public:
	ColorEditorProperty(const char* arg_title, glm::vec3& arg_values);

	void draw() override;
};

} // namespace
