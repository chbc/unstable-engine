#ifndef _PRIMITIVE_MESH_FACTORY_H_
#define _PRIMITIVE_MESH_FACTORY_H_

#include <engine/utils/memory_aliases.h>
#include "MeshData.h"

namespace sre
{

class Entity;
class Rect;

class PrimitiveMeshFactory
{
public:
	void createVerticesPlane2D(const glm::vec2 &size, const Rect &uv, const glm::vec2 &offset, std::vector<GUIVertexData> &result);
	UPTR<MeshData<GUIVertexData>> createPlane2D(const glm::vec2 &size);
	UPTR<MeshData<GUIVertexData>> createPlane2D(const glm::vec2 &size, const Rect &uv, float xOffset = 0.0f);
	UPTR<MeshData<VertexData>> createPlane(float size);
	UPTR<MeshData<VertexData>> createCube(float size);
	void createPlaneIndices(std::vector<uint32_t> &result, int planesCount = 1);

private:
	template <typename T>
	void getPlaneUVs(std::vector<T> &vertexData, float *planeTexCoords)
	{
		for (int i = 0; i < 4; i++)
		{
			vertexData[i].u = planeTexCoords[2 * i];
			vertexData[i].v = planeTexCoords[(2 * i) + 1];
		}
	}
};

} // namespace

#endif
