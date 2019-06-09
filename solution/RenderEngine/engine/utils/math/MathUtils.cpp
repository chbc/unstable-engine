#include "MathUtils.h"
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

namespace sre
{

void MathUtils::calculateTangentAndBitangent
(
	const glm::vec3 &pos1, const glm::vec3 &pos2, const glm::vec3 &pos3,
	const glm::vec2 &uv1, const glm::vec2 &uv2, const glm::vec2 &uv3,
	glm::vec3 &outTangent, glm::vec3 &outBitangent
)
{
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	outTangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	outTangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	outTangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	outTangent = glm::normalize(outTangent);

	outBitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	outBitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	outBitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	outBitangent = glm::normalize(outBitangent);
}

} // namespace
