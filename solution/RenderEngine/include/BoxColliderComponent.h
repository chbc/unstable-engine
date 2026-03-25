#pragma once

#include "AEntityComponent.h"
#include "Bounds.h"

#include <glm/vec3.hpp>

namespace sre
{

class SRE_API BoxColliderComponent : public AEntityComponent
{
DECLARE_COMPONENT()

private:
	Bounds bounds;

public:
	BoxColliderComponent(Entity* entity);
	bool intersects(BoxColliderComponent* other);

friend class PhysicsManager;
};

} // namespace
