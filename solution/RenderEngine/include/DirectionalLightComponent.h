#ifndef _DIRECTIONAL_LIGHT_COMPONENT_H_
#define _DIRECTIONAL_LIGHT_COMPONENT_H_

#include "ALightComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sre
{

class SRE_API DirectionalLightComponent : public ALightComponent
{
DECLARE_COMPONENT()

private:
	glm::vec3 direction;
    glm::mat4 lightSpaceMatrix;

public:
	DirectionalLightComponent(Entity *entity);
	void setDirection(const glm::vec3 &direction);
	glm::vec3 getDirection();

friend class Entity;
friend class ShadowRenderer;
friend class ShadowRendererShaderSetup;
};

} // namespace
#endif
