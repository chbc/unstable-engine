#include "PrimitiveMeshFactory.h"
#include <engine/utils/math/MathUtils.h>
#include <engine/utils/math/Rect.h>

namespace sre
{

UPTR<MeshData<GUIVertexData>> PrimitiveMeshFactory::createPlane2D(float width, float height)
{
	Rect uv(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	return createPlane2D(width, height, uv);
}

UPTR<MeshData<GUIVertexData>> PrimitiveMeshFactory::createPlane2D(float width, float height, const Rect &uv)
{
	float planeVertices[] = 
	{ 
		-width, height,
		-width,-height,
		width,-height,
		width, height
	};

	VECTOR_UPTR<GUIVertexData> vertexData;
	GUIVertexData *newData;
	// Positions
	for (int i = 0; i < 8; i += 2)
	{
		newData = new GUIVertexData;
		newData->position = glm::vec2(planeVertices[i], planeVertices[i + 1]);

		vertexData.emplace_back(newData);
	}

	// UVs
	float x1 = uv.topLeft.x;
	float y1 = uv.topLeft.y;
	float x2 = uv.topLeft.x + uv.size.x;
	float y2 = uv.topLeft.y + uv.size.y;

	float planeTexCoords[] =
	{
		x1, y1,
		x1, y2,
		x2, y2,
		x2, y1
	};
	getPlaneUVs(vertexData, planeTexCoords);

	// Indices
	std::vector<uint32_t> indices;
	getPlaneIndices(indices);

	return UPTR<MeshData<GUIVertexData>>{ new MeshData<GUIVertexData>{vertexData, indices} };
}

UPTR<MeshData<VertexData>> PrimitiveMeshFactory::createPlane(float size)
{
	float half = size * 0.5f;

	float planeVertices[] = 
	{ 
		half, half, 0,
		-half, half, 0,
		-half,-half, 0,
		half,-half, 0 
	};

	float planeNormals[] = 
	{ 
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1 
	};

	VECTOR_UPTR<VertexData> vertexData;
	VertexData *newData;
	// Positions and normals
	for (int i = 0; i < 12; i += 3)
	{
		newData = new VertexData;
		newData->position = glm::vec3(planeVertices[i], planeVertices[i + 1], planeVertices[i + 2]);
		newData->normal = glm::vec3(planeNormals[i], planeNormals[i + 1], planeNormals[i + 2]);

		vertexData.emplace_back(newData);
	}

	// UVs
	float planeTexCoords[] = 
	{ 
		1, 0,
		0, 0,
		0, 1,
		1, 1 
	};
	getPlaneUVs(vertexData, planeTexCoords);

	// Indices
	std::vector<uint32_t> indices;
	getPlaneIndices(indices);

	// Tangents and bitangents
	glm::vec3 tangent, bitangent;
	const int FACES_COUNT = 2;
	for (int i = 0; i < FACES_COUNT; i++)
	{
		MathUtils::calculateTangentAndBitangent
		(
			vertexData[indices[3*i]]->position, vertexData[indices[3*i + 1]]->position, vertexData[indices[3*i + 2]]->position,
			glm::vec2(vertexData[indices[3*i]]->u, vertexData[indices[3*i]]->v), 
			glm::vec2(vertexData[indices[3*i + 1]]->u, vertexData[indices[3*i + 1]]->v), 
			glm::vec2(vertexData[indices[3*i + 2]]->u, vertexData[indices[3*i + 2]]->v),
			tangent, bitangent
		);

		for (int j = 0; j < 2; j++)
		{
			vertexData[indices[3 * i + j]]->tangent = tangent;
			vertexData[indices[3 * i + j]]->bitangent = bitangent;
		}
	}

	return UPTR<MeshData<VertexData>>{ new MeshData<VertexData>{vertexData, indices} };
}

UPTR<MeshData<VertexData>> PrimitiveMeshFactory::createCube(float size)
{
	UPTR<MeshData<VertexData>> result;

	float half = size * 0.5f;

	float cubeVertices[] = 
	{ 
		half, half, half,  -half, half, half,  -half,-half, half,   half,-half, half,   // v0,v1,v2,v3 (front)
		half, half, half,   half,-half, half,   half,-half,-half,   half, half,-half,   // v0,v3,v4,v5 (right)
		half, half, half,   half, half,-half,  -half, half,-half,  -half, half, half,   // v0,v5,v6,v1 (top)
		-half, half, half,  -half, half,-half,  -half,-half,-half,  -half,-half, half,  // v1,v6,v7,v2 (left)
		-half,-half,-half,   half,-half,-half,   half,-half, half,  -half,-half, half,  // v7,v4,v3,v2 (bottom)
		half,-half,-half,  -half,-half,-half,  -half, half,-half,   half, half,-half	// v4,v7,v6,v5 (back)
	}; 

	float cubeNormals[] = 
	{ 
		0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
		1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
		0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
		-1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  // v1,v6,v7,v2 (left)
		0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
		0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1	// v4,v7,v6,v5 (back)
	};

	unsigned char cubeIndices[] = 
	{ 
		0, 1, 2,   2, 3, 0,     // front
		4, 5, 6,   6, 7, 4,     // right
		8, 9,10,  10,11, 8,     // top
		12,13,14,  14,15,12,    // left
		16,17,18,  18,19,16,    // bottom
		20,21,22,  22,23,20		// back
	};

	float cubeTexCoords[] = 
	{
		1, 0,	0, 0,	0, 1,	1, 1,
		0, 0,	0, 1,	1, 1,	1, 0,
		1, 1,	1, 0,	0, 0,	0, 1,
		1, 0,	0, 0,	0, 1,	1, 1,
		1, 1,	0, 1,	0, 0,	1, 0,
		0, 1,	1, 1,	1, 0,	0, 0 
	};

	VECTOR_UPTR<VertexData> vertexData;
	VertexData *newData;
	for (int i = 0; i < 72; i += 3)
	{
		newData = new VertexData;
		newData->position = glm::vec3(cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2]);
		newData->normal = glm::vec3(cubeNormals[i], cubeNormals[i + 1], cubeNormals[i + 2]);

		vertexData.emplace_back(newData);
	}

	for (int i = 0; i < 24; i++)
	{
		vertexData[i]->u = cubeTexCoords[2 * i];
		vertexData[i]->v = cubeTexCoords[(2 * i) + 1];
	}

	std::vector<uint32_t> indices;
	for (int i = 0; i < 36; i++)
		indices.push_back(cubeIndices[i]);

	result = UPTR<MeshData<VertexData>>{ new MeshData<VertexData>{vertexData, indices} };
	return result;
}

void PrimitiveMeshFactory::getPlaneIndices(std::vector<uint32_t> &result)
{
	unsigned char planeIndices[] = 
	{ 
		0, 1, 2,
		2, 3, 0 
	};

	for (int i = 0; i < 6; i++)
		result.push_back(planeIndices[i]);
}

} // namespace
