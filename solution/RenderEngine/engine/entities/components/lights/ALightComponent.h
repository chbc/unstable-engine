#ifndef _ALIGHT_COMPONENT_H_
#define _ALIGHT_COMPONENT_H_

#include <engine/entities/components/AEntityComponent.h>
#include <glm/vec3.hpp>

namespace sre
{

/*!
	Base class to handle lighting.
*/
class ALightComponent : public AEntityComponent
{
private:
	glm::vec3 color;

protected:
	ALightComponent(Entity *entity);

public:
    void setColor(const glm::vec3 &color);
	glm::vec3 getColor();
};

} // namespace

#endif
