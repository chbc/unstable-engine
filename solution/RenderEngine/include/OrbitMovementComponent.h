#pragma once

#include "AEntityComponent.h"
#include <glm/vec3.hpp>

namespace sre
{

class SRE_API OrbitMovementComponent : public AEntityComponent
{
	DECLARE_COMPONENT()

private:
	glm::vec3 target;

public:
	OrbitMovementComponent(Entity* entity);
	void move(const glm::vec2& deltaMovement, float elapsedTime);
};

} // namespace
