#ifndef _EMATERIAL_MAP_H_
#define _EMATERIAL_MAP_H_

#include <cstddef>

namespace sre
{

namespace EMaterialMap
{

enum Type : std::size_t
{
    COLOR = 0,
    GUI,
    DIFFUSE,
    NORMAL,
    SPECULAR,
    AMBIENT_OCCLUSION,
    SIZE
};

} // namespace

} // namespace
#endif
