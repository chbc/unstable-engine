#pragma once

#include "AColliderComponent.h"

#include <glm/vec3.hpp>

namespace sre
{

class SRE_API BoxColliderComponent : public AColliderComponent
{
DECLARE_COMPONENT()

public:
	BoxColliderComponent(Entity* entity);
	bool intersects(BoxColliderComponent* other);

friend class PhysicsManager;
};

} // namespace
