#ifndef _SCENE_BUTTON_H_
#define _SCENE_BUTTON_H_

#include "AEntityComponent.h"
#include <glm/vec3.hpp>

namespace sre
{

class SceneButtonComponent : public AEntityComponent
{
DECLARE_COMPONENT()

private:
	glm::vec3 extent;

private:
	SceneButtonComponent(Entity* entity, const glm::vec3& arg_extent);

	bool isInside();
};

} // namespace

#endif
