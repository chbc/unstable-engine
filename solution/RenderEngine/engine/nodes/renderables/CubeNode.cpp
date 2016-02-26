#include "CubeNode.h"
#include <engine/nodes/renderables/meshes/Mesh.h>
#include <engine/scene/SceneManager.h>

namespace sre
{

CubeNode::CubeNode(float size) : RenderableNode()
{
	float half = size * 0.5f;

	float cubeVertices[] = {half, half, half,  -half, half, half,  -half,-half, half,   half,-half, half,   // v0,v1,v2,v3 (front)
							half, half, half,   half,-half, half,   half,-half,-half,   half, half,-half,   // v0,v3,v4,v5 (right)
							half, half, half,   half, half,-half,  -half, half,-half,  -half, half, half,   // v0,v5,v6,v1 (top)
							-half, half, half,  -half, half,-half,  -half,-half,-half,  -half,-half, half,   // v1,v6,v7,v2 (left)
							-half,-half,-half,   half,-half,-half,   half,-half, half,  -half,-half, half,   // v7,v4,v3,v2 (bottom)
							half,-half,-half,  -half,-half,-half,  -half, half,-half,   half, half,-half }; // v4,v7,v6,v5 (back)

	float cubeNormals[]	= { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
							1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
							0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
							-1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
							0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
							0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)

	unsigned char cubeIndices[]	= { 0, 1, 2,   2, 3, 0,      // front
									4, 5, 6,   6, 7, 4,      // right
									8, 9,10,  10,11, 8,      // top
									12,13,14,  14,15,12,      // left
									16,17,18,  18,19,16,      // bottom
									20,21,22,  22,23,20 };    // back

    // TODO: armazenar as coordenadas de textura
	float cubeTexCoords[] = {1, 0,	0, 0,	0, 1,	1, 1,
							 0, 0,	0, 1,	1, 1,	1, 0,
							 1, 1,	1, 0,	0, 0,	0, 1,
							 1, 0,	0, 0,	0, 1,	1, 1,
							 1, 1,	0, 1,	0, 0,	1, 0,
							 0, 1,	1, 1,	1, 0,	0, 0 };

    std::vector<VertexData> *vertexData = new std::vector<VertexData>();
    for (int i = 0; i < 72; i += 3)
    {
        VertexData newData;
        newData.position = Vector(cubeVertices[i], cubeVertices[i + 1], cubeVertices[i+ 2]);
        newData.normal = Vector(cubeNormals[i], cubeNormals[i + 1], cubeNormals[i+ 2]);
        newData.color = Vector(1, 1, 1);

        vertexData->push_back(newData);
    }

    for (int i = 0; i < 24; i++)
    {
        vertexData->at(i).u = cubeTexCoords[2*i];
        vertexData->at(i).v = cubeTexCoords[(2*i) + 1];
    }

    std::vector<unsigned int> *indices = new std::vector<unsigned int>();
    for (int i = 0; i < 36; i++)
        indices->push_back(cubeIndices[i]);

    this->meshes.push_back(new Mesh(vertexData, indices));
}

} // namespace
