#pragma once

#include "ColorRendererComponent.h"

#include <cstdint>

namespace sre
{

class PBRRendererComponent : public ColorRendererComponent
{
protected:
    uint32_t albedoTextureId{ 0 };
    uint32_t normalTextureId{ 0 };
    uint32_t metallicTextureId{ 0 };
    uint32_t roughnessTextureId{ 0 };
    uint32_t aoTextureId{ 0 };

    int albedoTextureLocation{ 0 };
    int normalTextureLocation{ 0 };
    int metallicTextureLocation{ 0 };
    int roughnessTextureLocation{ 0 };
    int aoTextureLocation{ 0 };

protected:
    PBRRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    virtual void onSceneLoaded(uint32_t program) override;
    virtual void setupShaderValues(MeshComponent *mesh, uint32_t program) override;
    virtual void preDraw(uint32_t program) override;
    virtual void postDraw(uint32_t program) override;

friend class MeshRenderer;
};

} // namespace
