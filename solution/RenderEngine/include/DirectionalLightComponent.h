#ifndef _DIRECTIONAL_LIGHT_COMPONENT_H_
#define _DIRECTIONAL_LIGHT_COMPONENT_H_

#include "ALightComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sre
{

class SRE_API DirectionalLightComponent : public ALightComponent
{
private:
	glm::vec3 direction;
    glm::mat4 lightSpaceMatrix;

public:
	void setDirection(const glm::vec3 &direction);
	glm::vec3 getDirection();

private:
	DirectionalLightComponent(Entity *entity);

friend class Entity;
friend class ShadowRenderer;
friend class ShadowRendererShaderSetup;
};

} // namespace
#endif
