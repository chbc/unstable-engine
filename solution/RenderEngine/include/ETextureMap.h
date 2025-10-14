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
    IBL_BRDF_LUT,
    ENVIRONMENT_MAP,
    IBL_IRRADIANCE,
    IBL_PREFILTER,
    SHADOW,
    CUSTOM,
    EMPTY
};

} // namespace

} // namespace
