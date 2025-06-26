#pragma once

#include "core_defines.h"

#include <cstdint>

namespace sre
{

namespace ImGuiLib
{

SRE_API void begin(const char* title);
SRE_API void text(const char* format, const char* text = nullptr);
SRE_API void image(uint64_t textureId, float width, float height);
SRE_API void sameLine();
SRE_API void end();

} // namespace

} // namespace
