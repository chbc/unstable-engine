#ifndef _PRIMITIVE_MESH_FACTORY_H_
#define _PRIMITIVE_MESH_FACTORY_H_

#include <engine/utils/memory_aliases.h>
#include "MeshData.h"

namespace sre
{

class Entity;

class PrimitiveMeshFactory
{
public:
	static UPTR<MeshData<GUIVertexData>> createPlane2D(float width, float height, float *planeTexCoords);
	static UPTR<MeshData<GUIVertexData>> createPlane2D(float width, float height);
	static UPTR<MeshData<VertexData>> createPlane(float size);
	static UPTR<MeshData<VertexData>> createCube(float size);

private:
	static void getPlaneIndices(std::vector<uint32_t> &result);

	template <typename T>
	static void getPlaneUVs(VECTOR_UPTR<T> &vertexData, float *planeTexCoords)
	{
		for (int i = 0; i < 4; i++)
		{
			vertexData[i]->u = planeTexCoords[2 * i];
			vertexData[i]->v = planeTexCoords[(2 * i) + 1];
		}
	}
};

} // namespace

#endif
