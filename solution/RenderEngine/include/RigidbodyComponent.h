#pragma once

#include "AEntityComponent.h"

#include <glm/vec3.hpp>

namespace sre
{

class SRE_API RigidbodyComponent : public AEntityComponent
{
DECLARE_COMPONENT()

private:
	float mass{ 1.0f };
	glm::vec3 velocity{ 0.0f };
	glm::vec3 acceleration{ 0.0f };
	bool useGravity{ true };

public:
	RigidbodyComponent(Entity* entity) : AEntityComponent(entity) {}

friend class PhysicsManager;
};

} // namespace
