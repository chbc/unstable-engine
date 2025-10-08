#pragma once

#include <cstdint>

namespace sre
{

struct IBLData
{
	uint32_t irradianceMap{ 0 };
	uint32_t prefilterMap{ 0 };
	uint32_t brdfLUTMap{ 0 };
	bool loaded{ false };
};

} // namespace
