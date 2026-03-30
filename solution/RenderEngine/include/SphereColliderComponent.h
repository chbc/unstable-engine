#pragma once

#include "AColliderComponent.h"

#include <glm/vec3.hpp>

namespace sre
{

class SRE_API SphereColliderComponent : public AColliderComponent
{
DECLARE_COMPONENT()

private:
	float radius{ 0.5f };

public:
	SphereColliderComponent(Entity* entity);

friend class PhysicsManager;
};

} // namespace
