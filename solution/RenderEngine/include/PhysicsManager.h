#pragma once

#include "ASingleton.h"

#include <vector>
#include <glm/vec3.hpp>

namespace sre
{

class Entity;
class BoxColliderComponent;
class RigidbodyComponent;

class PhysicsManager : public ASingleton
{
private:
	std::vector<BoxColliderComponent*> staticObjects;
	std::vector<RigidbodyComponent*> dynamicObjects;

	static constexpr float GRAVITY{ -9.81f };

private:
	void addEntity(Entity* entity);
	void update(float elapsedTime);

	void updateVelocities(float elapsedTime);
	void updateCollisions(float elapsedTime);

	bool checkCollision(BoxColliderComponent* objectA, BoxColliderComponent* objectB);
	void resolvePosition(RigidbodyComponent* rigidbody, float elapsedTime);

	void cleanUp();

friend class ScenesManager;
friend class AScene;
};

} // namespace
