#ifndef _SHADOW_DATA_H_
#define _SHADOW_DATA_H_

#include <stdint.h>

struct ShadowData
{
    uint32_t fbo;
    uint32_t textureId;
    uint32_t textureUnit;

    ShadowData(uint32_t arg_fbo, uint32_t arg_textureId, uint32_t arg_textureUnit)
        : fbo(arg_fbo), textureId(arg_textureId), textureUnit(arg_textureUnit)
    { }
};

#endif
