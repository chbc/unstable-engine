#pragma once

#include "core_defines.h"

#include <glm/gtc/type_ptr.hpp>

namespace sre
{

namespace MathUtils
{
	void calculateTangentAndBitangent
	(
		const glm::vec3 &pos1, const glm::vec3 &pos2, const glm::vec3 &pos3,
		const glm::vec2 &uv1, const glm::vec2 &uv2, const glm::vec2 &uv3,
		glm::vec3 &outTangent, glm::vec3 &outBitangent
	);

	bool decomposeTransform(const glm::mat4& inputmatrix, glm::vec3& position, glm::vec3& scale, glm::vec3& rotation);

	bool SRE_API areNearlyEqual(const glm::vec3& vertex1, const glm::vec3& vertex2, const float threshold = 0.0001f);
}

} // namespace
