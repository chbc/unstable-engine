#pragma once

#include "AColliderComponent.h"

#include <glm/vec3.hpp>

namespace sre
{

class SRE_API SphereColliderComponent : public AColliderComponent
{
DECLARE_COMPONENT()

public:
	SphereColliderComponent(Entity* entity);
	float getRadius() const;

friend class PhysicsManager;
};

} // namespace
