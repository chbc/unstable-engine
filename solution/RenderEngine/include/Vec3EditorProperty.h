#pragma once

#include "AEditorProperty.h"
#include <glm/vec3.hpp>

namespace sre
{

class Vec3EditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	glm::vec3* value{ nullptr };
	float defaultValue{ 0.0f };

public:
	SRE_API Vec3EditorProperty(const char* arg_title, glm::vec3* arg_value, float arg_defaultValue = 0.0f);
};

} // namespace
