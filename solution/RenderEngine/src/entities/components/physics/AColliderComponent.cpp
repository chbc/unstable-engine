#include "AColliderComponent.h"
#include "SingletonsManager.h"
#include "PhysicsManager.h"
#include "BoolEditorProperty.h"
#include "Vec3EditorProperty.h"

namespace sre
{

IMPLEMENT_COMPONENT(AColliderComponent)

AColliderComponent::AColliderComponent(Entity* entity, ECollisionType arg_collisionType) 
	: AEntityComponent(entity), collisionType(arg_collisionType)
{
	this->addEditorProperty(new BoolEditorProperty{ "Blocking", &this->blocking });
	this->addEditorProperty(new Vec3EditorProperty{ "Center", &this->bounds.center });
}

AColliderComponent::~AColliderComponent()
{
	this->collisionAction = nullptr;
}

void AColliderComponent::setCollisionAction(const CollisionAction& action)
{
	this->collisionAction = action;
}

bool AColliderComponent::intersects(AColliderComponent* other, CollisionResult& result)
{
	PhysicsManager* physicsManager = SingletonsManager::Get<PhysicsManager>();
	return physicsManager->checkCollision(this, other, result);
}

bool AColliderComponent::intersects(AColliderComponent* other)
{
	PhysicsManager* physicsManager = SingletonsManager::Get<PhysicsManager>();
	return physicsManager->checkCollision(this, other);
}

const Bounds& AColliderComponent::getBounds() const
{
	return this->bounds;
}

ECollisionType AColliderComponent::getCollisionType() const
{
	return this->collisionType;
}

void AColliderComponent::notifyCollision(AColliderComponent* other, const CollisionResult& result)
{
	if (this->collisionAction)
	{
		this->collisionAction(other, result);
	}
}

} // namespace
