#pragma once

#include "AEntityComponent.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sre
{

class SRE_API OrbitMovementComponent : public AEntityComponent
{
	DECLARE_COMPONENT()

private:
	glm::vec3 target{ 0.0f, 0.0f, 0.0f };

public:
	OrbitMovementComponent(Entity* entity);
	void move(const glm::vec2& deltaMovement, float elapsedTime);
};

} // namespace
