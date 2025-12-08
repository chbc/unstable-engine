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
    METALLIC,
    ROUGHNESS,
    AMBIENT_OCCLUSION,

    IBL_BRDF_LUT,       // 6
    IBL_IRRADIANCE,
    IBL_PREFILTER,

    SKYBOX,             // 9
    CUSTOM,
	SHADOWS            // 11 - 14 (directional) | 15 - 18 (point)
};

} // namespace

} // namespace
