#pragma once
#include "ColorMeshData.h"

namespace sre
{

class Entity;
class Rect;

class PrimitiveMeshFactory
{
public:
	void createVerticesPlane2D(const glm::vec2 &size, const Rect &uv, const glm::vec2 &offset, std::vector<VertexData2D>& result);
	MeshData2D* createPlaneTopDown(const glm::vec2 &size);
	MeshData2D* createPlaneTopDown(const glm::vec2& size, const Rect& uv);
	MeshData2D* createPlaneBottomUp(const glm::vec2& size);
	MeshData* createPlane(float size, float tileMultiplier);
	MeshData* createPlane(const glm::vec2& size, float tileMultiplier);
	void createPlaneIndices(std::vector<uint32_t> &result, uint32_t planesCount = 1);
	MeshData* createCube(float size);
	MeshData* createSphere(float radius = 1.0f, uint16_t stackCount = 16, uint16_t sectorCount = 32);
	ColorMeshData* createBoxLines(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
	ColorMeshData* createBoxLines(const glm::vec4& color);

private:
	MeshData2D* createPlane2D(const glm::vec2 &size, const float* texCoords);
	void calculateTangentsAndBitangents(std::vector<VertexData>& vertexData, std::vector<uint32_t> indices, int facesCount);
	template <typename T>
	void getPlaneUVs(std::vector<T> &vertexData, const float *planeTexCoords)
	{
		for (int i = 0; i < 4; i++)
		{
			vertexData[i].u = planeTexCoords[2 * i];
			vertexData[i].v = planeTexCoords[(2 * i) + 1];
		}
	}

	void createSphereIndices(std::vector<uint32_t>& indices, uint16_t stackCount, uint16_t sectorCount);
};

} // namespace
