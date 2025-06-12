#pragma once

#include "Ray.h"

#include <vector>


namespace sre
{

struct VertexData;

struct Bounds
{
private:
	glm::vec3 center;
	glm::vec3 extents;
	glm::vec3 size;
	glm::vec3 min;
	glm::vec3 max;

public:
	Bounds() = default;
	void setup(const std::vector<VertexData>& vertexData);
	void setup(const glm::vec3& center, const glm::vec3& extents);
	bool intersects(const Ray& ray, const glm::vec3& worldPosition, float& distance) const;

private:
	void fixVertices();
};

} // namespace
