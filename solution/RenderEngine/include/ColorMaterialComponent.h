#pragma once

#include "AMaterialComponent.h"
#include <glm/vec4.hpp>

namespace sre
{

class Material;

class SRE_API ColorMaterialComponent : public AMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

private:
	glm::vec4 color; 

public:
	ColorMaterialComponent(Material *material);

	void setColor(const glm::vec4 &color);
	glm::vec4 getColor();
	void getColor(float* result);
};

} // namespace
