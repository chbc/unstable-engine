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
	AColliderComponent* collider = entity->getBaseComponent<AColliderComponent>();
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
	for (int i = 0; i < this->dynamicObjects.size(); ++i)
	{
		RigidbodyComponent* rigidbodyA = this->dynamicObjects[i];
		AColliderComponent* colliderA = rigidbodyA->getEntity()->getBaseComponent<AColliderComponent>();

		this->updateDynamicCollisions(rigidbodyA, colliderA, i);
		this->updateStaticCollisions(rigidbodyA, colliderA);
	}
}

void PhysicsManager::updateDynamicCollisions(RigidbodyComponent* rigidbodyA, AColliderComponent* colliderA, int sourceIndex)
{
	for (int j = sourceIndex + 1; j < this->dynamicObjects.size(); ++j)
	{
		RigidbodyComponent* rigidbodyB = this->dynamicObjects[j];
		AColliderComponent* colliderB = rigidbodyB->getEntity()->getBaseComponent<AColliderComponent>();
		CollisionResult collisionResult;
		if (this->checkCollision(colliderA, colliderB, collisionResult))
		{
			colliderA->notifyCollision(colliderB, collisionResult);
			colliderB->notifyCollision(colliderA, collisionResult);

			if (colliderA->blocking && colliderB->blocking)
			{
				this->resolveImpulses(rigidbodyA, rigidbodyB, collisionResult);
				this->resolvePositions(rigidbodyA, rigidbodyB, collisionResult);
			}
		}
	}
}

void PhysicsManager::updateStaticCollisions(RigidbodyComponent* rigidbody, AColliderComponent* dynamicCollider)
{
	for (AColliderComponent* staticCollider : this->staticObjects)
	{
		CollisionResult collisionResult;
		if (this->checkCollision(dynamicCollider, staticCollider, collisionResult))
		{
			dynamicCollider->notifyCollision(staticCollider, collisionResult);
			staticCollider->notifyCollision(dynamicCollider, collisionResult);

			if (dynamicCollider->blocking && staticCollider->blocking)
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
	else if ((colliderA->collisionType == ECollisionType::BOX) && (colliderB->collisionType == ECollisionType::SPHERE))
	{
		BoxColliderComponent* boxColliderA = static_cast<BoxColliderComponent*>(colliderA);
		SphereColliderComponent* sphereColliderB = static_cast<SphereColliderComponent*>(colliderB);
		glm::vec3 originA = positionA + boxColliderA->bounds.center;
		result = CollisionUtils::checkSphereBox
		(
			positionB, sphereColliderB->radius, originA, boxColliderA->bounds.halfExtents, collisionResult
		);
		collisionResult.normal = -collisionResult.normal;
	}
	else if ((colliderA->collisionType == ECollisionType::BOX) && (colliderB->collisionType == ECollisionType::BOX))
	{
		BoxColliderComponent* boxColliderA = static_cast<BoxColliderComponent*>(colliderA);
		BoxColliderComponent* boxColliderB = static_cast<BoxColliderComponent*>(colliderB);
		glm::vec3 originA = positionA + boxColliderA->bounds.center;
		glm::vec3 originB = positionB + boxColliderB->bounds.center;
		result = CollisionUtils::checkBoxBox
		(
			originA, boxColliderA->bounds.halfExtents, originB, boxColliderB->bounds.halfExtents, collisionResult
		);
	}

	return result;
}

bool PhysicsManager::checkCollision(AColliderComponent* objectA, AColliderComponent* objectB) const
{
	CollisionResult result;
	return this->checkCollision(objectA, objectB, result);
}

void PhysicsManager::resolveImpulses(RigidbodyComponent* rigidbodyA, RigidbodyComponent* rigidbodyB, const CollisionResult& collisionResult)
{
	float velocityAlongNormal = glm::dot(rigidbodyB->velocity - rigidbodyA->velocity, collisionResult.normal);
	if (velocityAlongNormal <= 0.0f)
	{
		float restitution = std::min(rigidbodyA->restitution, rigidbodyB->restitution);
		float magnitude = -(1 + restitution) * velocityAlongNormal;
		magnitude /= (1.0f / rigidbodyA->mass) + (1.0f / rigidbodyB->mass);

		glm::vec3 impulse = magnitude * collisionResult.normal;
		rigidbodyA->velocity -= (1.0f / rigidbodyA->mass) * impulse;
		rigidbodyB->velocity += (1.0f / rigidbodyB->mass) * impulse;
	}
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

void PhysicsManager::resolvePositions(RigidbodyComponent* rigidbodyA, RigidbodyComponent* rigidbodyB, const CollisionResult& collisionResult)
{
	const float SLOP = 0.01f;
	const float PERCENT = 0.2f;
	
	float depthResult = std::max(collisionResult.depth - SLOP, 0.0f);
	float inverseMassA = 1.0f / rigidbodyA->mass;
	float inverseMassB = 1.0f / rigidbodyB->mass;
	glm::vec3 correction = (depthResult / (inverseMassA + inverseMassB)) * PERCENT * collisionResult.normal;

	TransformComponent* transformA = rigidbodyA->getTransform();
	glm::vec3 positionA = transformA->getPosition();
	positionA -= inverseMassA * correction;
	transformA->setPosition(positionA);

	TransformComponent* transformB = rigidbodyB->getTransform();
	glm::vec3 positionB = transformB->getPosition();
	positionB += inverseMassB * correction;
	transformB->setPosition(positionB);
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
