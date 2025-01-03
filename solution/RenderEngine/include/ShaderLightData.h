#ifndef _SHADER_LIGHT_DATA
#define _SHADER_LIGHT_DATA

#include <stdint.h>

namespace sre
{

struct ShaderLightData
{
    bool receivesLight;
    bool hasAnyShadowCaster;

    size_t directionalLightsCount;
    size_t pointLightsCount;

    ShaderLightData() 
        :   receivesLight(false), hasAnyShadowCaster(false),
            directionalLightsCount(0), pointLightsCount(0)
    { }
};

} // namespace
#endif
