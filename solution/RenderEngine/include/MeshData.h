#pragma once

#include <vector>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace sre
{

struct ABaseVertexData
{
	float u{ 0.0f }, v{ 0.0f };

	static void *getUVOffset();
};

struct VertexData2D : public ABaseVertexData
{
	glm::vec2 position{ 0.0f };
	
	static void *getPositionOffset();
};

struct VertexData : public ABaseVertexData
{
	glm::vec3 position{ 0.0f };
	glm::vec3 normal{ 0.0f };
	glm::vec3 tangent{ 0.0f };
	glm::vec3 bitangent{ 0.0f };

	static void *getPositionOffset();
	static void *getNormalOffset();
	static void *getTangentOffset();
	static void *getBitangentOffset();
};

struct AMeshData
{
	std::vector<uint32_t> indices;
	uint32_t vao{0};
	uint32_t vbo{0};
	uint32_t ebo{0};

	AMeshData(const std::vector<uint32_t> &arg_indices)
		: indices(arg_indices), vao(0), vbo(0), ebo(0)
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
	std::string name;

	MeshData(std::string arg_name, const std::vector<VertexData>& arg_vertexData, const std::vector<uint32_t>& arg_indices)
		: AMeshData(arg_indices), vertexData(arg_vertexData), name(arg_name)
	{ }

	~MeshData() override
	{
		vertexData.clear();
	}

	bool operator==(const MeshData& other) const
	{
		return (this->vao == other.vao) && (this->vbo == other.vbo) && (this->ebo == other.ebo);
	}
};

struct MeshData2D : public AMeshData
{
	std::vector<VertexData2D> vertexData;
	std::string name;

	MeshData2D(std::string arg_name, const std::vector<VertexData2D>& arg_vertexData, const std::vector<uint32_t>& arg_indices)
		: AMeshData(arg_indices), vertexData(arg_vertexData), name(arg_name)
	{ }

	~MeshData2D() override
	{
		vertexData.clear();
	}
};

} // namespace
