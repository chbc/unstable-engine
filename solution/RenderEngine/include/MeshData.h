#ifndef _MESH_DATA_H_
#define _MESH_DATA_H_

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sre
{

struct ABaseVertexData
{
	float u, v;

	static void *getUVOffset();
};

struct GUIVertexData : public ABaseVertexData
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
	uint32_t vao;
	uint32_t vbo;
	uint32_t ebo;
	std::vector<uint16_t> indices;

	AMeshData(const std::vector<uint16_t> &arg_indices)
		: indices(arg_indices)
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

	MeshData(const std::vector<VertexData>& arg_vertexData, const std::vector<uint16_t>& arg_indices)
		: vertexData(arg_vertexData), AMeshData(arg_indices)
	{
	}

	~MeshData() override
	{
		vertexData.clear();
	}
};

struct GUIMeshData : public AMeshData
{
	std::vector<GUIVertexData> vertexData;

	GUIMeshData(const std::vector<GUIVertexData>& arg_vertexData, const std::vector<uint16_t>& arg_indices)
		: vertexData(arg_vertexData), AMeshData(arg_indices)
	{
	}

	~GUIMeshData() override
	{
		vertexData.clear();
	}
};

} // namespace

#endif
