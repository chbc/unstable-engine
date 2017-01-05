#ifndef _DIRECTIONAL_LIGHT_COMPONENT_H_
#define _DIRECTIONAL_LIGHT_COMPONENT_H_

#include "ALightComponent.h"

namespace sre
{

class DirectionalLightComponent : public ALightComponent
{
private:
	glm::vec3 direction;

public:
	void setDirection(const glm::vec3 &direction);
	glm::vec3 getDirection();

private:
	DirectionalLightComponent(Entity *entity);

friend class Entity;
};

} // namespace
#endif
