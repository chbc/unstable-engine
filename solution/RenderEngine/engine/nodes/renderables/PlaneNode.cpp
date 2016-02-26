#include "PlaneNode.h"
#include <engine/nodes/renderables/meshes/Mesh.h>
#include <engine/scene/SceneManager.h>
#include <iostream>

namespace sre
{

PlaneNode::PlaneNode(float size) : RenderableNode()
{
	float half = size * 0.5f;

	float planeVertices[] = { half, half, 0,
							 -half, half, 0,
							 -half,-half, 0,
							  half,-half, 0};

	float planeNormals[] = {0, 0, 1,
							0, 0, 1,
							0, 0, 1,
							0, 0, 1};

	unsigned char planeIndices[] =  {0, 1, 2,
									2, 3, 0};

    // TODO: armazenar as coordenadas de textura
	float planeTexCoords[] = {1, 0,
							  0, 0,
							  0, 1,
							  1, 1};


    std::vector<VertexData> *vertexData = new std::vector<VertexData>();
    VertexData newData;
    for (int i = 0; i < 12; i += 3)
    {
        newData.position = Vector(planeVertices[i], planeVertices[i + 1], planeVertices[i+ 2]);
        newData.normal = Vector(planeNormals[i], planeNormals[i + 1], planeNormals[i+ 2]);
        newData.color = Vector(1, 1, 1);

        vertexData->push_back(newData);
    }

    std::vector<unsigned int> *indices = new std::vector<unsigned int>();
    for (int i = 0; i < 6; i++)
        indices->push_back(planeIndices[i]);

    this->meshes.push_back(new Mesh(vertexData, indices));
}

} // namespace
