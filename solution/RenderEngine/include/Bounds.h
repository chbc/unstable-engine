#pragma once

#include "Ray.h"

#include <vector>


namespace sre
{

struct VertexData;

struct Bounds
{
public:
	glm::vec3 center{ 0.0f };
	glm::vec3 extents{ 0.0f };
	glm::vec3 size{ 0.0f };
	glm::vec3 min{ 0.0f };
	glm::vec3 max{ 0.0f };

public:
	Bounds() = default;
	void setup(const std::vector<VertexData>& vertexData);
	void setup(const glm::vec3& center, const glm::vec3& extents);
	bool intersects(const Ray& ray, const glm::vec3& worldPosition, float& distance) const;
	void add(const Bounds& other);

private:
	void fixVertices();
};

} // namespace
