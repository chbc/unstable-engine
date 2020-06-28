#ifndef _PRIMITIVE_MESH_FACTORY_H_
#define _PRIMITIVE_MESH_FACTORY_H_

#include "MeshData.h"

namespace sre
{

class Entity;
class Rect;

class PrimitiveMeshFactory
{
public:
	void createVerticesPlane2D(const glm::vec2 &size, const Rect &uv, const glm::vec2 &offset, std::vector<GUIVertexData> &result);
	GUIMeshData* createPlaneTopDown(const glm::vec2 &size);
	GUIMeshData* createPlaneTopDown(const glm::vec2& size, const Rect& uv);
	GUIMeshData* createPlaneBottomUp(const glm::vec2& size);
	GUIMeshData* createPlane2D(const glm::vec2 &size, const float* texCoords);
	MeshData* createPlane(float size, float tileMultiplier);
	MeshData* createCube(float size);
	MeshData* createSphere(float size);
	void createPlaneIndices(std::vector<uint32_t> &result, int planesCount = 1);

private:
	template <typename T>
	void getPlaneUVs(std::vector<T> &vertexData, const float *planeTexCoords)
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
