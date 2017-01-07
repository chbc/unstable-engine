#ifndef _POINT_LIGHT_COMPONENT_H_
#define _POINT_LIGHT_COMPONENT_H_

#include "ALightComponent.h"
#include <glm/vec3.hpp>

namespace sre
{

class PointLightComponent : public ALightComponent
{
public:
	void setPosition(const glm::vec3 &position);
	glm::vec3 getPosition();

private:
	PointLightComponent(Entity *entity);

friend class Entity;
};

} // namespace

#endif
