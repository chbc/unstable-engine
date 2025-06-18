#pragma once

#include "MeshData.h"

namespace sre
{

struct ColorMeshData : AMeshData
{
	std::vector<glm::vec3> vertexData;
	glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

	ColorMeshData(const std::vector<glm::vec3>& arg_vertexData,
		const std::vector<uint32_t>& arg_indices, glm::vec4 arg_color)
		: vertexData(arg_vertexData), color(arg_color), AMeshData(arg_indices)
	{
	}

	~ColorMeshData() override
	{
		vertexData.clear();
	}
};

} // namespace
