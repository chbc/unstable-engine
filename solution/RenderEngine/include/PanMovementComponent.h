#pragma once

#include "AEntityComponent.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sre
{

class SRE_API PanMovementComponent : public AEntityComponent
{
	DECLARE_COMPONENT()

public:
	PanMovementComponent(Entity* entity);
	void move(const glm::vec2& deltaMovement, float elapsedTime);
};

} // namespace
