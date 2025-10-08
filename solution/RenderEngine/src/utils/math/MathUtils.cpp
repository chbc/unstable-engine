#include "MathUtils.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/vec3.hpp>

namespace sre
{

namespace MathUtils
{

void calculateTangentAndBitangent
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

bool decomposeTransform(const glm::mat4& inputmatrix, glm::vec3& position, glm::vec3& scale, glm::vec3& rotation)
{
	using namespace glm;

	mat4 LocalMatrix(inputmatrix);

	// Normalize the matrix.
	if (epsilonEqual(LocalMatrix[3][3], 0.0f, epsilon<float>()))
		return false;

	for (length_t i = 0; i < 4; ++i)
		for (length_t j = 0; j < 4; ++j)
			LocalMatrix[i][j] /= LocalMatrix[3][3];

	// Next take care of translation (easy).
	position = vec3(LocalMatrix[3]);
	LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

	vec3 Row[3];

	// Now get scale and shear.
	for (length_t i = 0; i < 3; ++i)
		for (length_t j = 0; j < 3; ++j)
			Row[i][j] = LocalMatrix[i][j];

	// Compute X scale factor and normalize first row.
	scale.x = length(Row[0]);
	Row[0] = detail::scale(Row[0], 1.0f);
	scale.y = length(Row[1]);
	Row[1] = detail::scale(Row[1], 1.0f);
	scale.z = length(Row[2]);
	Row[2] = detail::scale(Row[2], 1.0f);

	rotation.y = asin(-Row[0][2]);
	if (cos(rotation.y) != 0)
	{
		rotation.x = atan2(Row[1][2], Row[2][2]);
		rotation.z = atan2(Row[0][1], Row[0][0]);
	}
	else
	{
		rotation.x = atan2(-Row[2][0], Row[1][1]);
		rotation.z = 0;
	}

	return true;
}

bool areNearlyEqual(const glm::vec3& vertex1, const glm::vec3& vertex2, const float threshold)
{
	return
	(
		glm::epsilonEqual(vertex1.x, vertex2.x, threshold) &&
		glm::epsilonEqual(vertex1.y, vertex2.y, threshold) &&
		glm::epsilonEqual(vertex1.z, vertex2.z, threshold)
	);
}

} // namespace

} // namespace
