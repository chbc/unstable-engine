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
	MeshData* createPlane(float size, float tileMultiplier);
	MeshData* createPlane(const glm::vec2& size, float tileMultiplier);
	MeshData* createCube(float size);
	MeshData* createSphere(float radius = 1.0f, uint16_t rings = 16, uint16_t sectors = 32);
	void createPlaneIndices(std::vector<uint16_t> &result, int planesCount = 1);

private:
	GUIMeshData* createPlane2D(const glm::vec2 &size, const float* texCoords);
	template <typename T>
	void getPlaneUVs(std::vector<T> &vertexData, const float *planeTexCoords)
	{
		for (int i = 0; i < 4; i++)
		{
			vertexData[i].u = planeTexCoords[2 * i];
			vertexData[i].v = planeTexCoords[(2 * i) + 1];
		}
	}

	void pushSphereIndices(std::vector<uint16_t>& indices, int sectors, int r, int s);
};

} // namespace

#endif
