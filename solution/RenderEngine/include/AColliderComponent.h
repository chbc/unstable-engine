#pragma once

#include "AEntityComponent.h"

#include <glm/vec3.hpp>
#include <functional>

namespace sre
{

class AColliderComponent;
struct CollisionResult;

using CollisionAction = std::function<void(AColliderComponent*, const CollisionResult&)>;

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
	CollisionAction collisionAction;
	ECollisionType collisionType;
	bool blocking{ true };

public:
	AColliderComponent(Entity* entity, ECollisionType arg_collisionType = ECollisionType::NONE);
	virtual ~AColliderComponent() = default;

public:
	void setCollisionAction(const CollisionAction& action);
	bool intersects(AColliderComponent* other, CollisionResult& result);
	bool intersects(AColliderComponent* other);

protected:
	virtual void onDestroy() override;

private:
	void notifyCollision(AColliderComponent* other, const CollisionResult& result);

friend class PhysicsManager;
};

} // namespace
