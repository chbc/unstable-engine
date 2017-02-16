#ifndef _VERTEX_DATA_H_
#define _VERTEX_DATA_H_

#include <glm/vec3.hpp>

namespace sre
{

struct VertexData
{
    glm::vec3 position;
    glm::vec3 normal;
    float u, v;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

} // namespace

#endif // _VERTEX_DATA_H_
