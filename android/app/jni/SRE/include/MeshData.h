#ifndef _MESH_DATA_H_
#define _MESH_DATA_H_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "memory_aliases.h"

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

template <typename T>
struct MeshData
{
	std::vector<T> vertexData;
	std::vector<uint32_t> indices;

	MeshData(const std::vector<T> &arg_vertexData, const std::vector<uint32_t> &arg_indices)
		: vertexData(arg_vertexData), indices(arg_indices)
	{
	}

	~MeshData()
	{
		vertexData.clear();
		this->indices.clear();
	}
};

} // namespace

#endif
