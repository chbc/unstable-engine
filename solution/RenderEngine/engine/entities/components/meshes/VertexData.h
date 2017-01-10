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
};

} // namespace

#endif // _VERTEX_DATA_H_
