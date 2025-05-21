#pragma once

#include <cstddef>

namespace sre
{

namespace ETextureMap
{

enum Type : std::size_t
{
    GUI = 0,
    DIFFUSE,
    NORMAL,
    SPECULAR,
    AMBIENT_OCCLUSION,
    METALLIC,
    ROUGHNESS,
    SHADOW,
    CUBE_MAP,
    EMPTY
};

} // namespace

} // namespace
