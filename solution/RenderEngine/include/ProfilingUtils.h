#pragma once
#include <cstdint>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>

#define PROFILE_CPU_ZONE(name, color) ZoneScopedNC(name, color)
#define PROFILE_GPU_ZONE(name, color) GpuProfileScope tracyGpuScope(name, color)

class ProfilingUtils
{
public:
	static void onFrameEnd();
};

class GpuProfileScope
{
public:
    GpuProfileScope(const char* name, uint32_t color);
    ~GpuProfileScope();

private:
    alignas(16) char _storage[64];
};

#else
    #define PROFILE_CPU_ZONE(name, color)
    #define PROFILE_GPU_ZONE(name, color)

class ProfilingUtils
{
public:
    static void onFrameEnd() {}
};

#endif
