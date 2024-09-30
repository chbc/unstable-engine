#pragma once

#include "AEditorProperty.h"
#include <glm/vec3.hpp>
#include <functional>

namespace sre
{

class Vec3EditorProperty : public AEditorProperty
{
private:
	glm::vec3* values;
	std::function<void(void)> onValuesChanged;
	float defaultValue;

public:
	Vec3EditorProperty(const char* arg_title, glm::vec3* arg_values, float arg_defaultValue = 0.0f);
	Vec3EditorProperty(const char* arg_title, glm::vec3* arg_values, std::function<void()> onValuesChanged, float arg_defaultValue = 0.0f);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
