#pragma once

#include "ColorRendererComponent.h"

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;

class OutlineRendererComponent : public ColorRendererComponent
{

protected:
    OutlineRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    virtual void onSceneLoaded(uint32_t program) override;
    virtual void setupShaderValues(class MeshComponent *mesh, uint32_t program) override;
    virtual void preDraw(uint32_t program) override;
    virtual void postDraw(uint32_t program) override;

friend class MeshRenderer;
};

} // namespace
