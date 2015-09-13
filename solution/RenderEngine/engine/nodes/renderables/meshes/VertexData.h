#ifndef _VERTEX_DATA_H_
#define _VERTEX_DATA_H_

#include <engine/math/Vector.h>

struct VertexData
{
    Vector position;
    Vector normal;
    Vector color;
    float u, v;
};

#endif // _VERTEX_DATA_H_
