#pragma once

#include "AEditorProperty.h"
#include <glm/vec2.hpp>

namespace sre
{

class Vec2EditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	glm::vec2* value{ nullptr };
	float defaultValue{ 0.0f };

public:
	SRE_API Vec2EditorProperty(const char* arg_title, glm::vec2* arg_value, float arg_defaultValue = 0.0f);
};

} // namespace
