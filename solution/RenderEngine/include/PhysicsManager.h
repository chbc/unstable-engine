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

	static constexpr float GRAVITY{ -9.81f };

private:
	void addEntity(Entity* entity);
	void update(float elapsedTime);

	void updateVelocities(float elapsedTime);
	void updateCollisions(float elapsedTime);

	bool checkCollision(AColliderComponent* objectA, AColliderComponent* objectB, CollisionResult& collisionResult) const;
	bool checkCollision(AColliderComponent* objectA, AColliderComponent* objectB) const;
	void resolveImpulse(RigidbodyComponent* rigidbody, const CollisionResult& collisionResult);
	void resolvePosition(RigidbodyComponent* rigidbody, const CollisionResult& collisionResult);

	void cleanUp();

friend class ScenesManager;
friend class AScene;
friend class AColliderComponent;

};

} // namespace
