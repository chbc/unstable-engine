#pragma once

#include <cstddef>

namespace sre
{

namespace EComponentId
{

enum Type : std::size_t
{
    COLOR_MATERIAL = 0,
    LIT_MATERIAL,
    DIFFUSE_MATERIAL,
    NORMAL_MATERIAL,
    SPECULAR_MATERIAL,
    AO_MATERIAL,
    PBR_MATERIAL,
	SPRITE_MATERIAL,
    CUSTOM_MATERIAL,
    SECOND_TARGET_COLOR_MATERIAL, // XXX INCOMPLETO
    SIZE
};

} // namespace

} // namespace
