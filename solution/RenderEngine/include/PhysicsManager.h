#pragma once

#include "ASingleton.h"

#include <vector>
#include <glm/vec3.hpp>

namespace sre
{

class Entity;
class AColliderComponent;
class RigidbodyComponent;
struct CollisionResult;

class PhysicsManager : public ASingleton
{
private:
	std::vector<AColliderComponent*> staticObjects;
	std::vector<RigidbodyComponent*> dynamicObjects;

	float accumulator{ 0.0f };
	static constexpr float GRAVITY{ -9.81f };
	static constexpr float TIME_STEP = 1.0f / 60.0f;

private:
	void addEntity(Entity* entity);
	void update(float elapsedTime);
	void step(float timeStep);

	void updateVelocities(float timeStep);
	void updateCollisions();
	void updateDynamicCollisions(RigidbodyComponent* rigidbodyA, AColliderComponent* colliderA, int sourceIndex);
	void updateStaticCollisions(RigidbodyComponent* rigidbody, AColliderComponent* dynamicCollider);

	bool checkCollision(AColliderComponent* objectA, AColliderComponent* objectB, CollisionResult& collisionResult) const;
	bool checkCollision(AColliderComponent* objectA, AColliderComponent* objectB) const;
	void resolveImpulses(RigidbodyComponent* rigidbodyA, RigidbodyComponent* rigidbodyB, const CollisionResult& collisionResult);
	void resolveImpulse(RigidbodyComponent* rigidbody, const CollisionResult& collisionResult);
	void resolvePosition(RigidbodyComponent* rigidbody, const CollisionResult& collisionResult);
	void resolvePositions(RigidbodyComponent* rigidbodyA, RigidbodyComponent* rigidbodyB, const CollisionResult& collisionResult);

	void cleanUp();

friend class ScenesManager;
friend class AScene;
friend class AColliderComponent;

};

} // namespace
