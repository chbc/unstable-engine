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
    uint32_t depthCubemap;
    uint32_t fbo;

public:
	void setPosition(const glm::vec3 &position);
	glm::vec3 getPosition();

	void setRange(float range);
	float getRange();

	void setIntensity(float intensity);
	float getIntensity();

private:
	PointLightComponent(Entity *entity);

friend class Entity;
friend class ShadowRenderer;
friend class ShadowRendererShaderSetup;
};

} // namespace

#endif
