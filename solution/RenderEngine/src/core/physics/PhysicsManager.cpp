#include "PhysicsManager.h"
#include "Entity.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"

namespace sre
{

void PhysicsManager::addEntity(Entity* entity)
{
	BoxColliderComponent* collider = entity->getComponent<BoxColliderComponent>();
	RigidbodyComponent* rigidbody = entity->getComponent<RigidbodyComponent>();
	if (collider)
	{
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
	this->updateVelocities(elapsedTime);
	this->updateCollisions(elapsedTime);
}

void PhysicsManager::updateVelocities(float elapsedTime)
{
	for (RigidbodyComponent* rigidbody : this->dynamicObjects)
	{
		if (rigidbody->useGravity)
		{
			rigidbody->acceleration.y += GRAVITY;
		}
		rigidbody->velocity += rigidbody->acceleration * elapsedTime;
		rigidbody->acceleration = glm::vec3(0.0f);

		TransformComponent* transform = rigidbody->getTransform();
		glm::vec3 newPosition = transform->getPosition();
		newPosition += rigidbody->velocity * elapsedTime;
		transform->setPosition(newPosition);
	}
}

void PhysicsManager::updateCollisions(float elapsedTime)
{
	for (RigidbodyComponent* rigidbody : this->dynamicObjects)
	{
		for (BoxColliderComponent* staticCollider : this->staticObjects)
		{
			BoxColliderComponent* dynamicCollider = rigidbody->getEntity()->getComponent<BoxColliderComponent>();
			if (this->checkCollision(dynamicCollider, staticCollider))
			{
				this->resolvePosition(rigidbody, elapsedTime);
			}
		}
	}
}

bool PhysicsManager::checkCollision(BoxColliderComponent* colliderA, BoxColliderComponent* colliderB)
{
	return (colliderA && colliderB) ? colliderA->intersects(colliderB) : false;
}

void PhysicsManager::resolvePosition(RigidbodyComponent* rigidbody, float elapsedTime)
{
	TransformComponent* transform = rigidbody->getTransform();
	glm::vec3 position = transform->getPosition();
	position = position - (rigidbody->velocity * elapsedTime);
	transform->setPosition(position);
	rigidbody->velocity = glm::vec3{ 0.0f };
	rigidbody->acceleration = glm::vec3{ 0.0f };
}

void PhysicsManager::cleanUp()
{
	this->staticObjects.clear();
	this->dynamicObjects.clear();
}

} // namespace
