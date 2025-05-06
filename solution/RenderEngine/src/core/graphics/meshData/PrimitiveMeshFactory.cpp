#include "PrimitiveMeshFactory.h"
#include "MathUtils.h"
#include "Rect.h"

#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923

namespace sre
{

void PrimitiveMeshFactory::createVerticesPlane2D(const glm::vec2 &size, const Rect &uv, const glm::vec2 &offset, std::vector<VertexData2D>& result)
{
	float planeVertices[] = 
	{ 
		offset.x,            offset.y + size.y,
		offset.x,            offset.y - size.y,
		size.x*2 + offset.x, offset.y - size.y,
		size.x*2 + offset.x, offset.y + size.y
	};

	// Positions
	std::vector<VertexData2D> verticesData;
	VertexData2D newData; 
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
	
	for (VertexData2D item : verticesData)
	{
		result.emplace_back(item);
	}
}

MeshData2D* PrimitiveMeshFactory::createPlaneTopDown(const glm::vec2& size)
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

MeshData2D* PrimitiveMeshFactory::createPlaneTopDown(const glm::vec2& size, const Rect& uv)
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

MeshData2D* PrimitiveMeshFactory::createPlaneBottomUp(const glm::vec2& size)
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

MeshData* PrimitiveMeshFactory::createPlane(float size, float tileMultiplier)
{
	return this->createPlane(glm::vec2(size, size), tileMultiplier);
}

MeshData* PrimitiveMeshFactory::createPlane(const glm::vec2& size, float tileMultiplier)
{
	glm::vec2 half = size * 0.5f;

	float planeVertices[] = 
	{ 
		half.x, 0.0f, -half.y,
		-half.x, 0.0f, -half.y,
		-half.x, 0.0f, half.y,
		half.x,	0.0f, half.y
	};

	float planeNormals[] = 
	{ 
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f 
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
		tileMultiplier, 0.0f,
		0.0f, 0.0f,
		0.0f, tileMultiplier,
		tileMultiplier, tileMultiplier
	};
	getPlaneUVs(vertexData, planeTexCoords);

	// Indices
	std::vector<uint32_t> indices;
	createPlaneIndices(indices);

	this->calculateTangentsAndBitangents(vertexData, indices, 2);
	return new MeshData{"Plane", vertexData, indices};
}

void PrimitiveMeshFactory::createPlaneIndices(std::vector<uint32_t>& result, uint32_t planesCount)
{
	uint32_t baseIndices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};

	for (uint32_t planeIndex = 0; planeIndex < planesCount; planeIndex++)
	{
		for (uint32_t i = 0; i < 6; i++)
			result.push_back(baseIndices[i] + (4 * planeIndex));
	}
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

	uint32_t cubeIndices[] =
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

	std::vector<uint32_t> indices;
	for (int i = 0; i < 36; i++)
		indices.push_back(cubeIndices[i]);

	this->calculateTangentsAndBitangents(vertexData, indices, 12);

	return new MeshData{"Cube", vertexData, indices};
}

MeshData* PrimitiveMeshFactory::createSphere(float radius, uint16_t stackCount, uint16_t sectorCount)
{
	std::vector<VertexData> vertexData;
	std::vector<uint32_t> indices;
	
	vertexData.resize((stackCount + 1) * (sectorCount + 1));

	std::vector<VertexData>::iterator item = vertexData.begin();

	float x, y, z, xy;
	float lengthInv = 1.0f / radius;
	float sectorStep = static_cast<float>(2 * M_PI) / static_cast<float>(sectorCount);
	float stackStep = static_cast<float>(M_PI) / static_cast<float>(stackCount);
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = static_cast<float>(M_PI / 2) - (i * stackStep);        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

			(*item).position.x = x;
			(*item).position.y = y;
			(*item).position.z = z;

			(*item).normal.x = x * lengthInv;
			(*item).normal.y = y * lengthInv;
			(*item).normal.z = z * lengthInv;

			(*item).u = static_cast<float>(j) / sectorCount;
			(*item).v = static_cast<float>(i)/ stackCount;

			item++;
		}
	}

	this->createSphereIndices(indices, stackCount, sectorCount);

	int midStacks = stackCount - 2;
	int faces = (sectorCount * 2) + (midStacks * sectorCount * 2);
	this->calculateTangentsAndBitangents(vertexData, indices, faces);

	return new MeshData{"Sphere", vertexData, indices};
}

MeshData2D* PrimitiveMeshFactory::createPlane2D(const glm::vec2& size, const float* texCoords)
{
	float planeVertices[] =
	{
		-size.x, size.y,
		-size.x,-size.y,
		 size.x,-size.y,
		 size.x, size.y
	};

	std::vector<VertexData2D> vertexData;
	// Positions
	for (int i = 0; i < 8; i += 2)
	{
		VertexData2D newData;
		newData.position = glm::vec2(planeVertices[i], planeVertices[i + 1]);

		vertexData.emplace_back(newData);
	}

	getPlaneUVs(vertexData, texCoords);

	// Indices
	std::vector<uint32_t> indices;
	createPlaneIndices(indices);

	return new MeshData2D{"Plane2D", vertexData, indices};
}

void PrimitiveMeshFactory::calculateTangentsAndBitangents(std::vector<VertexData>& vertexData, std::vector<uint32_t> indices, int facesCount)
{
	// Tangents and bitangents
	glm::vec3 tangent, bitangent;
	for (int i = 0; i < facesCount; i++)
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
}

void PrimitiveMeshFactory::createSphereIndices(std::vector<uint32_t>& indices, uint16_t stackCount, uint16_t sectorCount)
{
	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
}

} // namespace
