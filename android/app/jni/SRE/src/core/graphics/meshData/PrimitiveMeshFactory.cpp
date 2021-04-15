#include "PrimitiveMeshFactory.h"
#include "MathUtils.h"
#include "Rect.h"

namespace sre
{

void PrimitiveMeshFactory::createVerticesPlane2D(const glm::vec2 &size, const Rect &uv, const glm::vec2 &offset, std::vector<GUIVertexData> &result)
{
	float planeVertices[] = 
	{ 
		offset.x,            offset.y + size.y,
		offset.x,            offset.y - size.y,
		size.x*2 + offset.x, offset.y - size.y,
		size.x*2 + offset.x, offset.y + size.y
	};

	// Positions
	std::vector<GUIVertexData> verticesData;
	GUIVertexData newData; 
	for (int i = 0; i < 8; i += 2)
	{
		newData.position = glm::vec2(planeVertices[i], planeVertices[i + 1]);
		verticesData.emplace_back(newData);
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
	getPlaneUVs(verticesData, planeTexCoords);
	
	for (GUIVertexData item : verticesData)
	{
		result.emplace_back(item);
	}
}

GUIMeshData* PrimitiveMeshFactory::createPlaneTopDown(const glm::vec2& size)
{
	float planeTexCoords[] =
	{
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	return createPlane2D(size, planeTexCoords);
}

GUIMeshData* PrimitiveMeshFactory::createPlaneTopDown(const glm::vec2& size, const Rect& uv)
{
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

	return this->createPlane2D(size, planeTexCoords);
}

GUIMeshData* PrimitiveMeshFactory::createPlaneBottomUp(const glm::vec2& size)
{
	float planeTexCoords[] =
	{
		0, 1,
		0, 0,
		1, 0,
		1, 1
	};

	return createPlane2D(size, planeTexCoords);
}

GUIMeshData* PrimitiveMeshFactory::createPlane2D(const glm::vec2 &size, const float* texCoords)
{
	float planeVertices[] = 
	{ 
		-size.x, size.y,
		-size.x,-size.y,
		 size.x,-size.y,
		 size.x, size.y
	};

	std::vector<GUIVertexData> vertexData;
	// Positions
	for (int i = 0; i < 8; i += 2)
	{
		GUIVertexData newData;
		newData.position = glm::vec2(planeVertices[i], planeVertices[i + 1]);

		vertexData.emplace_back(newData);
	}

	getPlaneUVs(vertexData, texCoords);

	// Indices
	std::vector<uint16_t> indices;
	createPlaneIndices(indices);

	return new GUIMeshData{vertexData, indices};
}

MeshData* PrimitiveMeshFactory::createPlane(float size, float tileMultiplier)
{
	return this->createPlane(glm::vec2(size, size), tileMultiplier);
}

MeshData* PrimitiveMeshFactory::createPlane(const glm::vec2& size, float tileMultiplier)
{
	glm::vec2 half = size * 0.5f;

	float planeVertices[] = 
	{ 
		half.x,	half.y, 0,
		-half.x,half.y, 0,
		-half.x,-half.y, 0,
		half.x,	-half.y, 0 
	};

	float planeNormals[] = 
	{ 
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1 
	};

	std::vector<VertexData> vertexData;
	// Positions and normals
	for (int i = 0; i < 12; i += 3)
	{
		VertexData newData;
		newData.position = glm::vec3(planeVertices[i], planeVertices[i + 1], planeVertices[i + 2]);
		newData.normal = glm::vec3(planeNormals[i], planeNormals[i + 1], planeNormals[i + 2]);

		vertexData.emplace_back(newData);
	}
	
	// UVs
	float planeTexCoords[] = 
	{ 
		tileMultiplier, 0,
		0, 0,
		0, tileMultiplier,
		tileMultiplier, tileMultiplier
	};
	getPlaneUVs(vertexData, planeTexCoords);

	// Indices
	std::vector<uint16_t> indices;
	createPlaneIndices(indices);

	// Tangents and bitangents
	glm::vec3 tangent, bitangent;
	const int FACES_COUNT = 2;
	for (int i = 0; i < FACES_COUNT; i++)
	{
		MathUtils::calculateTangentAndBitangent
		(
			vertexData[indices[3*i]].position, vertexData[indices[3*i + 1]].position, vertexData[indices[3*i + 2]].position,
			glm::vec2(vertexData[indices[3*i]].u, vertexData[indices[3*i]].v), 
			glm::vec2(vertexData[indices[3*i + 1]].u, vertexData[indices[3*i + 1]].v),
			glm::vec2(vertexData[indices[3*i + 2]].u, vertexData[indices[3*i + 2]].v),
			tangent, bitangent
		);

		for (int j = 0; j < 2; j++)
		{
			vertexData[indices[3 * i + j]].tangent = tangent;
			vertexData[indices[3 * i + j]].bitangent = bitangent;
		}
	}

	return new MeshData{vertexData, indices};
}

MeshData* PrimitiveMeshFactory::createCube(float size)
{
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

	std::vector<VertexData> vertexData;
	for (int i = 0; i < 72; i += 3)
	{
		VertexData newData;
		newData.position = glm::vec3(cubeVertices[i], cubeVertices[i + 1], cubeVertices[i + 2]);
		newData.normal = glm::vec3(cubeNormals[i], cubeNormals[i + 1], cubeNormals[i + 2]);

		vertexData.emplace_back(newData);
	}

	for (int i = 0; i < 24; i++)
	{
		vertexData[i].u = cubeTexCoords[2 * i];
		vertexData[i].v = cubeTexCoords[(2 * i) + 1];
	}

	std::vector<uint16_t> indices;
	for (int i = 0; i < 36; i++)
		indices.push_back(cubeIndices[i]);

	// Tangents and bitangents
	glm::vec3 tangent, bitangent;
	const int FACES_COUNT = 12;
	for (int i = 0; i < FACES_COUNT; i++)
	{
		MathUtils::calculateTangentAndBitangent
		(
			vertexData[indices[3 * i]].position, vertexData[indices[3 * i + 1]].position, vertexData[indices[3 * i + 2]].position,
			glm::vec2(vertexData[indices[3 * i]].u, vertexData[indices[3 * i]].v),
			glm::vec2(vertexData[indices[3 * i + 1]].u, vertexData[indices[3 * i + 1]].v),
			glm::vec2(vertexData[indices[3 * i + 2]].u, vertexData[indices[3 * i + 2]].v),
			tangent, bitangent
		);

		for (int j = 0; j < 2; j++)
		{
			vertexData[indices[3 * i + j]].tangent = tangent;
			vertexData[indices[3 * i + j]].bitangent = bitangent;
		}
	}

	return new MeshData{ vertexData, indices };
}

MeshData* PrimitiveMeshFactory::createSphere(float size)
{
	return nullptr;
}

void PrimitiveMeshFactory::createPlaneIndices(std::vector<uint16_t> &result, int planesCount)
{
	unsigned char baseIndices[] = 
	{ 
		0, 1, 2,
		2, 3, 0,
	};

	for (int planeIndex = 0; planeIndex < planesCount; planeIndex++)
	{
		for (int i = 0; i < 6; i++)
			result.push_back(baseIndices[i] + (4 * planeIndex));
	}
}

} // namespace
