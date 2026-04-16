#pragma once

#include "AEntityComponent.h"
#include "Bounds.h"
#include "ECollisionType.h"

namespace sre
{

class AColliderComponent;
struct CollisionResult;

using CollisionAction = std::function<void(AColliderComponent*, const CollisionResult&)>;

class SRE_API AColliderComponent : public AEntityComponent
{

DECLARE_COMPONENT()

protected:
	Bounds bounds;

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
	const Bounds& getBounds() const;
	ECollisionType getCollisionType() const;

protected:
	virtual void onDestroy() override;

private:
	void notifyCollision(AColliderComponent* other, const CollisionResult& result);

friend class PhysicsManager;
};

} // namespace
