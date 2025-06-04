#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sre
{

class MathUtils
{
public:
	static void calculateTangentAndBitangent
	(
		const glm::vec3 &pos1, const glm::vec3 &pos2, const glm::vec3 &pos3,
		const glm::vec2 &uv1, const glm::vec2 &uv2, const glm::vec2 &uv3,
		glm::vec3 &outTangent, glm::vec3 &outBitangent
	);
};

} // namespace
