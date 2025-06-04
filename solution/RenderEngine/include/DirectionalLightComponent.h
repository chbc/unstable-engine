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
	glm::mat4 lightSpaceMatrix{ 1.0f };

public:
	DirectionalLightComponent(Entity *entity);

friend class Entity;
friend class ShadowRenderer;
friend class ShadowRendererShaderSetup;
};

} // namespace
#endif
