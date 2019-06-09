#ifndef _POINT_LIGHT_COMPONENT_H_
#define _POINT_LIGHT_COMPONENT_H_

#include "ALightComponent.h"
#include <glm/vec3.hpp>

namespace sre
{

class PointLightComponent : public ALightComponent
{
private:
	float range;
	float intensity;

private:
    PointLightComponent(Entity *entity);

public:
	void setPosition(const glm::vec3 &position);
	glm::vec3 getPosition();

	void setRange(float range);
	float getRange();

	void setIntensity(float intensity);
	float getIntensity();

friend class Entity;
};

} // namespace

#endif
