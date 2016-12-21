#include "MeshFactory.h"
#include <engine/entities/Entity.h>
#include "MeshComponent.h"

namespace sre
{

MeshComponent *MeshFactory::createPlane(Entity *entity, float size)
{
	MeshComponent *result{ nullptr };

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

	unsigned char planeIndices[] = 
	{ 
		0, 1, 2,
		2, 3, 0 
	};

	/*
	// ### armazenar as coordenadas de textura
	float planeTexCoords[] = 
	{ 
		1, 0,
		0, 0,
		0, 1,
		1, 1 
	};
	*/

	VECTOR_UPTR<VertexData> vertexData;
	VertexData *newData;
	for (int i = 0; i < 12; i += 3)
	{
		newData = new VertexData;
		newData->position = glm::vec3(planeVertices[i], planeVertices[i + 1], planeVertices[i + 2]);
		newData->normal = glm::vec3(planeNormals[i], planeNormals[i + 1], planeNormals[i + 2]);
		newData->color = glm::vec3(1.0f, 1.0f, 1.0f);

		vertexData.emplace_back(newData);
	}

	std::vector<uint32_t> indices;
	for (int i = 0; i < 6; i++)
		indices.push_back(planeIndices[i]);

	result = entity->addComponent<MeshComponent>(vertexData, indices);

	return result;
}

MeshComponent *MeshFactory::createCube(Entity *entity, float size)
{
	MeshComponent *result{ nullptr };

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

	// TODO: armazenar as coordenadas de textura
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
		newData->color = glm::vec3(1.0f, 1.0f, 1.0f);

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

	result = entity->addComponent<MeshComponent>(vertexData, indices);

	return result;
}

} // namespace
