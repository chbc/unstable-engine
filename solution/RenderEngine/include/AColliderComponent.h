#pragma once

#include "AEntityComponent.h"
#include <glm/vec3.hpp>

namespace sre
{

struct CollisionResult;

enum class ECollisionType : uint16_t
{
	NONE,
	BOX,
	SPHERE
};

class SRE_API AColliderComponent : public AEntityComponent
{

DECLARE_COMPONENT()

private:
	ECollisionType collisionType;

public:
	AColliderComponent(Entity* entity, ECollisionType arg_collisionType = ECollisionType::NONE);
	virtual ~AColliderComponent() = default;

public:
	bool intersects(AColliderComponent* other, CollisionResult& result);
	bool intersects(AColliderComponent* other);

friend class PhysicsManager;
};

} // namespace
