#pragma once

#include <cstdint>

namespace sre
{

namespace EDrawMode
{
    enum Type : uint32_t
    {
        POINTS = 0,
        LINES = 1,
        LINE_LOOP = 2,
        LINE_STRIP = 3,
        TRIANGLES = 4,
        TRIANGLE_STRIP = 5,
        TRIANGLE_FAN = 6,
        LINES_AND_POINTS = 7
    };
} // namespace EDrawMode

} // namespace sre
