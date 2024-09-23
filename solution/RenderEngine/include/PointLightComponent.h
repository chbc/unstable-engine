#ifndef _POINT_LIGHT_COMPONENT_H_
#define _POINT_LIGHT_COMPONENT_H_

#include "ALightComponent.h"
#include <glm/vec3.hpp>

namespace sre
{

class SRE_API PointLightComponent : public ALightComponent
{
DECLARE_COMPONENT()

private:
	float range;
	float intensity;

public:
    PointLightComponent(Entity *entity);
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
