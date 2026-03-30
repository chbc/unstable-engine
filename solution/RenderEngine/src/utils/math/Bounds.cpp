#include "Bounds.h"
#include "MeshData.h"
#include "CollisionUtils.h"

namespace sre
{

void Bounds::setup(const std::vector<VertexData>& vertexData)
{
	glm::vec3 minVertex = vertexData[0].position;
	glm::vec3 maxVertex = vertexData[0].position;
	for (const auto& vertex : vertexData)
	{
		minVertex = glm::min(minVertex, vertex.position);
		maxVertex = glm::max(maxVertex, vertex.position);
	}

	this->center = (minVertex + maxVertex) * 0.5f;
	this->halfExtents = (maxVertex - minVertex) * 0.5f;

	this->fixVertices();
}

bool Bounds::intersects(const glm::vec3 position, const glm::vec3 otherPosition, const Bounds& other)
{
	CollisionResult collisionResult;
	
	glm::vec3 origin = position + this->center;
	glm::vec3 otherOrigin = otherPosition + other.center;
	return CollisionUtils::checkBoxBox
	(
		origin, this->halfExtents, otherOrigin, other.halfExtents, collisionResult
	);
}

bool Bounds::intersects(const Ray& ray, const glm::mat4& worldMatrix, float& distance) const
{
	bool result = false;

	glm::vec3 worldMin = this->center - this->halfExtents;
	glm::vec3 worldMax = this->center + this->halfExtents;

	worldMin = worldMatrix * glm::vec4{ worldMin, 1.0f };
	worldMax = worldMatrix * glm::vec4{ worldMax, 1.0f };

	glm::vec3 invDir = 1.0f / ray.direction;
	glm::vec3 t0 = (worldMin - ray.origin) * invDir;
	glm::vec3 t1 = (worldMax - ray.origin) * invDir;
	float tmin = std::max(std::max(std::min(t0.x, t1.x), std::min(t0.y, t1.y)), std::min(t0.z, t1.z));
	float tmax = std::min(std::min(std::max(t0.x, t1.x), std::max(t0.y, t1.y)), std::max(t0.z, t1.z));

	if (tmax >= 0 && tmax >= tmin)
	{
		distance = (tmin < 0) ? tmax : tmin;
		result = true;
	}

	return result;
}

void Bounds::add(const Bounds& other)
{
	this->center += other.center;
	this->halfExtents = glm::max(this->halfExtents, other.halfExtents);
	this->fixVertices();
}

const glm::vec3 Bounds::getSize() const
{
	return (this->halfExtents * 2.0f);
}

void Bounds::reset()
{
	this->center = glm::vec3{ 0.0f };
	this->halfExtents = glm::vec3{ 0.0f };
}

void Bounds::fixVertices()
{
	if (halfExtents.x < 0.0001f)
	{
		halfExtents.x = 0.0001f;
	}

	if (halfExtents.y < 0.0001f)
	{
		halfExtents.y = 0.0001f;
	}

	if (halfExtents.z < 0.0001f)
	{
		halfExtents.z = 0.0001f;
	}
}

} // namespace
