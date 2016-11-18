#ifndef _ALIGHT_COMPONENT_H_
#define _ALIGHT_COMPONENT_H_

#include <engine/entities/components/AEntityComponent.h>
#include <glm/vec3.hpp>

/* ###
enum ELightType
{
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT = 1
};
*/

namespace sre
{

class TransformComponent;

/*!
	Base class to handle lighting.
*/
class ALightComponent : public AEntityComponent
{
	private:
		glm::vec3 color;

	protected:
		TransformComponent *transform;
		// ### float range;

		ALightComponent(Entity *entity);

	public:
        void setColor(const glm::vec3 &color);
        // ### virtual ELightType getType() =0;

    friend class LightManager;
};

} // namespace

#endif
