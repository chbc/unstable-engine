#ifndef _POINT_LIGHT_COMPONENT_H_
#define _POINT_LIGHT_COMPONENT_H_

#include "ALightComponent.h"

namespace sre
{

class PointLightComponent : public ALightComponent
{
private:
	PointLightComponent(Entity *entity);

public:
	// ELightType getType();

friend class Entity;
};

} // namespace

#endif
