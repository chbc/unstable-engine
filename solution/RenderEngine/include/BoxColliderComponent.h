#pragma once

#include "AColliderComponent.h"
#include "Bounds.h"

#include <glm/vec3.hpp>

namespace sre
{

class SRE_API BoxColliderComponent : public AColliderComponent
{
DECLARE_COMPONENT()

private:
	Bounds bounds;

public:
	BoxColliderComponent(Entity* entity);
	bool intersects(BoxColliderComponent* other);
	const Bounds& getBounds() const;

friend class PhysicsManager;
};

} // namespace
