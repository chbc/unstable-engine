#pragma once

#include "LitRendererNoLightsState.h"

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;

class LitRendererLightsState : public LitRendererNoLightsState
{
private:
    void onSceneLoaded(ShaderManager *shaderManager, uint32_t program) override;
    void setupShaderValues(ShaderManager *shaderManager, class MeshComponent *mesh, uint32_t program) override;
    void preDraw(AGraphicsWrapper *graphicsWrapper) override;
    void postDraw(AGraphicsWrapper *graphicsWrapper) override;
};

} // namespace
