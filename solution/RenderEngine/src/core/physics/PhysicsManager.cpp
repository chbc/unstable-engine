#include "PhysicsManager.h"
#include "Entity.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "CollisionUtils.h"

namespace sre
{

void PhysicsManager::addEntity(Entity* entity)
{
	AColliderComponent* collider = entity->getComponent<AColliderComponent>();
	if (collider)
	{
		RigidbodyComponent* rigidbody = entity->getComponent<RigidbodyComponent>();
		if (rigidbody)
		{
			this->dynamicObjects.push_back(rigidbody);
		}
		else
		{
			this->staticObjects.push_back(collider);
		}
	}
}

void PhysicsManager::update(float elapsedTime)
{
	if (elapsedTime > 0.25f)
	{
		elapsedTime = 0.25f;
	}

	this->accumulator += elapsedTime;

	while (accumulator >= TIME_STEP)
	{
		this->step(TIME_STEP);
		this->accumulator -= TIME_STEP;
	}
}

void PhysicsManager::step(float timeStep)
{
	this->updateVelocities(timeStep);
	this->updateCollisions();

}

void PhysicsManager::updateVelocities(float timeStep)
{
	for (RigidbodyComponent* rigidbody : this->dynamicObjects)
	{
		if (rigidbody->useGravity)
		{
			rigidbody->acceleration.y += GRAVITY;
		}
		rigidbody->velocity += rigidbody->acceleration * timeStep;
		rigidbody->acceleration = glm::vec3(0.0f);

		TransformComponent* transform = rigidbody->getTransform();
		glm::vec3 newPosition = transform->getPosition();
		newPosition += rigidbody->velocity * timeStep;
		transform->setPosition(newPosition);
	}
}

void PhysicsManager::updateCollisions()
{
	for (RigidbodyComponent* rigidbody : this->dynamicObjects)
	{
		for (AColliderComponent* staticCollider : this->staticObjects)
		{
			AColliderComponent* dynamicCollider = rigidbody->getEntity()->getComponent<AColliderComponent>();
			CollisionResult collisionResult;
			if (this->checkCollision(dynamicCollider, staticCollider, collisionResult))
			{
				this->resolveImpulse(rigidbody, collisionResult);
				this->resolvePosition(rigidbody, collisionResult);
			}
		}
	}
}

bool PhysicsManager::checkCollision(AColliderComponent* colliderA, AColliderComponent* colliderB, CollisionResult& collisionResult) const
{
	bool result = false;

	glm::vec3 positionA = colliderA->getTransform()->getPosition();
	glm::vec3 positionB = colliderB->getTransform()->getPosition();

	if ((colliderA->collisionType == ECollisionType::SPHERE) && (colliderB->collisionType == ECollisionType::SPHERE))
	{
		SphereColliderComponent* sphereColliderA = static_cast<SphereColliderComponent*>(colliderA);
		SphereColliderComponent* sphereColliderB = static_cast<SphereColliderComponent*>(colliderB);

		result = CollisionUtils::checkSphereSphere
		(
			positionA, sphereColliderA->radius, positionB, sphereColliderB->radius,	collisionResult
		);
	}
	else if ((colliderA->collisionType == ECollisionType::SPHERE) && (colliderB->collisionType == ECollisionType::BOX))
	{
		SphereColliderComponent* sphereColliderA = static_cast<SphereColliderComponent*>(colliderA);
		BoxColliderComponent* boxColliderB = static_cast<BoxColliderComponent*>(colliderB);
		glm::vec3 originB = positionB + boxColliderB->bounds.center;

		result = CollisionUtils::checkSphereBox
		(
			positionA, sphereColliderA->radius, originB, boxColliderB->bounds.halfExtents, collisionResult 
		);
	}

	return result;
}

bool PhysicsManager::checkCollision(AColliderComponent* objectA, AColliderComponent* objectB) const
{
	CollisionResult result;
	return this->checkCollision(objectA, objectB, result);
}

void PhysicsManager::resolveImpulse(RigidbodyComponent* rigidbody, const CollisionResult& collisionResult)
{
	float velocityAlongNormal = glm::dot(-rigidbody->velocity, collisionResult.normal);

	if (velocityAlongNormal <= 0.0f)
	{
		float magnitude = -(1 + rigidbody->restitution) * velocityAlongNormal;
		magnitude /= (1.0f / rigidbody->mass);

		glm::vec3 impulse = magnitude * collisionResult.normal;
		rigidbody->velocity -= (1.0f / rigidbody->mass) * impulse;
	}
}

void PhysicsManager::resolvePosition(RigidbodyComponent* rigidbody, const CollisionResult& collisionResult)
{
	const float SLOP = 0.01f;
	const float PERCENT = 0.2f;
	
	float depthResult = std::max(collisionResult.depth - SLOP, 0.0f);
	float inverseMass = 1.0f / rigidbody->mass;
	glm::vec3 correction = (depthResult / inverseMass) * PERCENT * collisionResult.normal;

	TransformComponent* transform = rigidbody->getTransform();
	glm::vec3 position = transform->getPosition();
	position = position - (inverseMass * correction);
	transform->setPosition(position);
}

void PhysicsManager::cleanUp()
{
	this->staticObjects.clear();
	this->dynamicObjects.clear();
}

} // namespace
