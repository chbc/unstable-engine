#ifndef _E_COMPONENT_ID_H_
#define _E_COMPONENT_ID_H_

#include <cstddef>

namespace sre
{

namespace EComponentId
{

enum Type : std::size_t
{
    TRANSFORM = 0,
    CAMERA,
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    MESH,
	POST_PROCESSING,

    COLOR_MATERIAL,
    LIT_MATERIAL,
    DIFFUSE_MATERIAL,
    NORMAL_MATERIAL,
    SPECULAR_MATERIAL,
    AO_MATERIAL,
	SPRITE_MATERIAL,
    SECOND_TARGET_COLOR_MATERIAL,

    GUI_IMAGE,
    GUI_TEXT,

    SIZE
};

} // namespace

} // namespace
#endif
