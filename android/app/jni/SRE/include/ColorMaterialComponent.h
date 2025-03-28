#ifndef _COLOR_MATERIAL_COMPONENT_H_
#define _COLOR_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include <glm/vec4.hpp>


namespace sre
{

class Material;

class SRE_API ColorMaterialComponent : public AMaterialComponent
{
private:
	glm::vec4 color; 

public:
	ColorMaterialComponent(Material *material);

	void setColor(const glm::vec4 &color);
	glm::vec4 getColor();
};

} // namespace
#endif
