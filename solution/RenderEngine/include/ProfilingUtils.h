#pragma once

#include <tracy/Tracy.hpp>
#include <string>

#ifdef TRACY_ENABLE
    #define PROFILING_CPU_ZONE(name, color) ZoneScopedNC(name, color)
    #define PROFILING_FRAME_MARK FrameMark
#else
    #define PROFILING_CPU_ZONE(name, color)
    #define PROFILING_FRAME_MARK
#endif

namespace sre
{

class ProfilingUtils
{
public:
    static void PlotValue(const char* name, int64_t value)
    {
#ifdef TRACY_ENABLE
        TracyPlot(name, value);
#endif
    }

    static void Log(const std::string& message, uint32_t color = 0xFFFFFF)
    {
#ifdef TRACY_ENABLE
        TracyMessageC(message.c_str(), message.size(), color);
#endif
    }
};

} // namespace
