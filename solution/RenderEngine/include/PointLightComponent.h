#pragma once

#include "ALightComponent.h"
#include <glm/mat4x4.hpp>

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
	void setRange(float range);
	float getRange();

	void setIntensity(float intensity);
	float getIntensity();

friend class Entity;
};

} // namespace
