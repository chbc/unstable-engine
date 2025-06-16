#pragma once

#include "ColorRendererComponent.h"

#include <cstdint>

namespace sre
{

class DiffuseRendererComponent : public ColorRendererComponent
{
protected:
    uint32_t textureId;
    int textureLocation;

protected:
    DiffuseRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    virtual void onSceneLoaded(uint32_t program) override;
    virtual void setupShaderValues(MeshComponent *mesh, uint32_t program) override;
    virtual void preDraw(uint32_t program) override;
    virtual void postDraw(uint32_t program) override;

friend class MeshRenderer;
};

} // namespace
