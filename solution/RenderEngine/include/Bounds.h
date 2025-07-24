#pragma once

#include "Ray.h"

#include <vector>
#include <glm/mat4x4.hpp>

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
	bool intersects(const Ray& ray, const glm::mat4& worldMatrix, float& distance) const;
	void add(const Bounds& other);
	void reset();

private:
	void fixVertices();
};

} // namespace
