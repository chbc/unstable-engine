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
	glm::vec3 halfExtents{ 0.0f };

public:
	Bounds() = default;
	void setup(const std::vector<VertexData>& vertexData);
	bool intersects(const glm::vec3 position, const glm::vec3 otherPosition, const Bounds& other);
	bool intersects(const Ray& ray, const glm::mat4& worldMatrix, float& distance) const;
	void add(const Bounds& other);
	const glm::vec3 getSize() const;
	float getRadius() const;
	void reset(float halfExtent = 0.0f);

private:
	void fixVertices();
};

} // namespace
