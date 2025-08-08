#include "Bounds.h"
#include "MeshData.h"

#include <algorithm>

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
	this->extents = (maxVertex - minVertex) * 0.5f;
	this->size = this->extents * 2.0f;
	this->min = minVertex;
	this->max = maxVertex;

	this->fixVertices();
}

bool Bounds::intersects(const Ray& ray, const glm::mat4& worldMatrix, float& distance) const
{
	bool result = false;

	glm::vec3 worldMin = this->min;
	glm::vec3 worldMax = this->max;

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
	this->min = glm::min(this->min, other.min);
	this->max = glm::max(this->max, other.max);
	this->center = (this->min + this->max) * 0.5f;
	this->extents = (this->max - this->min) * 0.5f;
	this->size = this->extents * 2.0f;
	this->fixVertices();
}

void Bounds::reset()
{
	this->center = glm::vec3{ 0.0f };
	this->extents = glm::vec3{ 0.0f };
	this->size = glm::vec3{ 0.0f };
	this->min = glm::vec3{ 0.0f };
	this->max = glm::vec3{ 0.0f };
}

void Bounds::fixVertices()
{
	if (this->max.x - this->min.x < 0.0001f)
	{
		this->max.x += 0.0001f;
		this->min.x -= 0.0001f;
	}

	if (this->max.y - this->min.y < 0.0001f)
	{
		this->max.y += 0.0001f;
		this->min.y -= 0.0001f;
	}

	if (this->max.z - this->min.z < 0.0001f)
	{
		this->max.z += 0.0001f;
		this->min.z -= 0.0001f;
	}
}

} // namespace
