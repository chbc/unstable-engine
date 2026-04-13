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

	glm::vec3 closestPointB = glm::clamp(positionA, originB - halfExtentsB, originB + halfExtentsB);
	glm::vec3 toObjectB = closestPointB - positionA;
	float distanceSquared = glm::length2(toObjectB);

	if (distanceSquared < radiusA * radiusA)
	{
		result = true;
		float distance = glm::sqrt(distanceSquared);
		collisionResult.depth = radiusA - distance;
		collisionResult.normal = (distance != 0.0f) ? toObjectB / distance : glm::vec3{ 0.0f, 1.0f, 0.0 };
	}

	return result;
}

bool checkBoxBox(
    const glm::vec3& originA, const glm::vec3& halfExtentsA,
    const glm::vec3& originB, const glm::vec3& halfExtentsB,
    CollisionResult& collisionResult
)
{
	bool result = false;
    glm::vec3 distance = originB - originA;

    float x_overlap = (halfExtentsA.x + halfExtentsB.x) - std::abs(distance.x);
    float y_overlap = (halfExtentsA.y + halfExtentsB.y) - std::abs(distance.y);
    float z_overlap = (halfExtentsA.z + halfExtentsB.z) - std::abs(distance.z);

    if (!(x_overlap <= 0 || y_overlap <= 0 || z_overlap <= 0))
	{
		result = true;

		if (x_overlap < y_overlap && x_overlap < z_overlap)
		{
			collisionResult.depth = x_overlap;
			collisionResult.normal = glm::vec3(distance.x > 0 ? 1 : -1, 0, 0);
		}
		else if (y_overlap < z_overlap)
		{
			collisionResult.depth = y_overlap;
			collisionResult.normal = glm::vec3(0, distance.y > 0 ? 1 : -1, 0);
		}
		else
		{
			collisionResult.depth = z_overlap;
			collisionResult.normal = glm::vec3(0, 0, distance.z > 0 ? 1 : -1);
		}
    }

    return result;
}

} // namespace CollectionsUtils

} // namespace sre
