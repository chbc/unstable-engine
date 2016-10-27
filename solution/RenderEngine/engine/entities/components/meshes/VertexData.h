#ifndef _VERTEX_DATA_H_
#define _VERTEX_DATA_H_

#include <engine/math/Vector.h>

namespace sre
{

struct VertexData
{
    Vector position;
    Vector normal;
    Vector color;
    float u, v;
};

} // namespace

#endif // _VERTEX_DATA_H_
