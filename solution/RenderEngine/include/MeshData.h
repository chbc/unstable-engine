#pragma once

#include "memory_aliases.h"

#include <vector>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace sre
{

struct ABaseVertexData
{
	float u, v;

	static void *getUVOffset();
};

struct VertexData2D : public ABaseVertexData
{
	glm::vec2 position;
	
	static void *getPositionOffset();
};

struct VertexData : public ABaseVertexData
{
    glm::vec3 position;
    glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	static void *getPositionOffset();
	static void *getNormalOffset();
	static void *getTangentOffset();
	static void *getBitangentOffset();
};

struct AMeshData
{
	std::string name;
	std::vector<uint32_t> indices;
	uint32_t vao;
	uint32_t vbo;
	uint32_t ebo;

	AMeshData(std::string arg_name, const std::vector<uint32_t> &arg_indices)
		: name(arg_name), indices(arg_indices), vao(0), vbo(0), ebo(0)
	{
	}

	virtual ~AMeshData()
	{
		this->indices.clear();
	}
};

struct MeshData : public AMeshData
{
	std::vector<VertexData> vertexData;

	MeshData(std::string arg_name, const std::vector<VertexData>& arg_vertexData, const std::vector<uint32_t>& arg_indices)
		: vertexData(arg_vertexData), AMeshData(arg_name, arg_indices)
	{
	}

	~MeshData() override
	{
		vertexData.clear();
	}
};

struct MeshData2D : public AMeshData
{
	std::vector<VertexData2D> vertexData;

	MeshData2D(std::string arg_name, const std::vector<VertexData2D>& arg_vertexData, const std::vector<uint32_t>& arg_indices)
		: vertexData(arg_vertexData), AMeshData(arg_name, arg_indices)
	{
	}

	~MeshData2D() override
	{
		vertexData.clear();
	}
};

} // namespace
