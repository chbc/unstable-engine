#pragma once

#include "ColorRendererComponent.h"
#include "LitRendererLightsState.h"
#include "memory_aliases.h"

namespace sre
{

class LitRendererComponent : public ColorRendererComponent
{
private:
    UPTR<LitRendererNoLightsState> state;

protected:
    LitRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    virtual void onSceneLoaded(uint32_t program) override;
    virtual void setupShaderValues(class MeshComponent *mesh, uint32_t program) override;
    virtual void preDraw(uint32_t program) override;
    virtual void postDraw(uint32_t program) override;

    friend class MeshRenderer;
};

} // namespace
