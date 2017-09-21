#ifndef _MESH_DATA_H_
#define _MESH_DATA_H_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <engine/utils/memory_aliases.h>

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
	VECTOR_UPTR<T> vertexData;
	std::vector<uint32_t> indices;

	MeshData(VECTOR_UPTR<T> &vertexData, const std::vector<uint32_t> &indices)
		: vertexData(std::move(vertexData)), indices(indices)
	{ }

	~MeshData()
	{
		this->vertexData.clear();
		this->indices.clear();
	}
};

} // namespace

#endif
