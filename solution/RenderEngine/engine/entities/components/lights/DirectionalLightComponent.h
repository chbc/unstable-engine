#ifndef _DIRECTIONAL_LIGHT_COMPONENT_H_
#define _DIRECTIONAL_LIGHT_COMPONENT_H_

#include "ALightComponent.h"

namespace sre
{

class DirectionalLightComponent : public ALightComponent
{
	private:
		DirectionalLightComponent(Entity *entity);

	public:
		// ### ELightType getType();

	friend class Entity;
};

} // namespace
#endif
