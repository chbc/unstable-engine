#ifndef _EMATERIAL_MAP_H_
#define _EMATERIAL_MAP_H_

#include <cstddef>

namespace sre
{

namespace EMaterialMap
{

enum Type : std::size_t
{
    GUI = 0,
    DIFFUSE,
    NORMAL,
    SPECULAR,
    AMBIENT_OCCLUSION,
    SHADOW,
    SIZE
};

} // namespace

} // namespace
#endif
