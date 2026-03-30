#include "CollisionUtils.h"

#include <glm/gtx/norm.hpp>

namespace sre
{

namespace CollisionUtils
{

bool checkSphereSphere
(
	const glm::vec3& positionA, float radiusA,
	const glm::vec3& positionB,	float radiusB,
	CollisionResult& collisionResult
)
{
	bool result = false;
	glm::vec3 toObjectB = positionB - positionA;

	float distanceSquared = glm::length2(toObjectB);
	float radiusSum = radiusA + radiusB;
	if (distanceSquared < radiusSum * radiusSum)
	{
		result = true;
		float distance = glm::sqrt(distanceSquared);
		collisionResult.depth = radiusSum - distance;
		collisionResult.normal = (distance != 0.0f) ? toObjectB / distance : glm::vec3{ 0.0f, 1.0f, 0.0 };
	}

	return result;
}

bool checkSphereBox
(
	const glm::vec3& positionA, float radiusA,
	const glm::vec3& originB, const glm::vec3& halfExtentsB,
	CollisionResult& collisionResult
)
{
	bool result = false;

	glm::vec3 closestPoint = glm::clamp(positionA, originB - halfExtentsB, originB + halfExtentsB);
	glm::vec3 direction = positionA - closestPoint;
	float distance = glm::length(direction);

	if (distance < radiusA)
	{
		collisionResult.normal = glm::normalize(direction);
		collisionResult.depth = radiusA - distance;
	}

	return result;
}

bool checkBoxBox
(
	const glm::vec3& originA, const glm::vec3& halfExtentsA,
	const glm::vec3& originB, const glm::vec3& halfExtentsB,
	CollisionResult& collisionResult
)
{
	bool result =
	!(
		((originA.x + halfExtentsA.x) < (originB.x - halfExtentsB.x)) ||
		((originA.x - halfExtentsA.x) > (originB.x + halfExtentsB.x)) ||
		((originA.y + halfExtentsA.y) < (originB.y - halfExtentsB.y)) ||
		((originA.y - halfExtentsA.y) > (originB.y + halfExtentsB.y)) ||
		((originA.z + halfExtentsA.z) < (originB.z - halfExtentsB.z)) ||
		((originA.z - halfExtentsA.z) > (originB.z + halfExtentsB.z))
	);

	return result;
}

} // namespace CollectionsUtils

} // namespace sre
