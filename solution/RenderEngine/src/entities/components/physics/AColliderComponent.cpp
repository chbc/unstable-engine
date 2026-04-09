#include "AColliderComponent.h"
#include "SingletonsManager.h"
#include "PhysicsManager.h"
#include "BoolEditorProperty.h"

namespace sre
{

IMPLEMENT_COMPONENT(AColliderComponent)

AColliderComponent::AColliderComponent(Entity* entity, ECollisionType arg_collisionType) 
	: AEntityComponent(entity), collisionType(arg_collisionType)
{
	this->addEditorProperty(new BoolEditorProperty{ "Blocking", &this->blocking });
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

void AColliderComponent::onDestroy()
{
	this->collisionAction = nullptr;
}

void AColliderComponent::notifyCollision(AColliderComponent* other, const CollisionResult& result)
{
	if (this->collisionAction)
	{
		this->collisionAction(other, result);
	}
}

} // namespace
