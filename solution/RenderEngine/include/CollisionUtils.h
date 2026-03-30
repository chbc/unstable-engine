#pragma once

#include <glm/vec3.hpp>

namespace sre
{

struct CollisionResult
{
	glm::vec3 normal;
	float depth{ 0 };
};

namespace CollisionUtils
{

bool checkSphereSphere
(
	const glm::vec3& positionA, float radiusA,
	const glm::vec3& positionB, float radiusB,
	CollisionResult& collisionResult
);

bool checkSphereBox
(
	const glm::vec3& positionA, float radiusA,
	const glm::vec3& originB, const glm::vec3& halfExtentsB,
	CollisionResult& collisionResult
);

bool checkBoxBox
(
	const glm::vec3& originA, const glm::vec3& halfExtentsA,
	const glm::vec3& originB, const glm::vec3& halfExtentsB,
	CollisionResult& collisionResult
);

} // namespace CollisionUtils

} // namespace sre
