#ifndef _LIT_RENDERER_LIGHTS_STATE_H_
#define _LIT_RENDERER_LIGHTS_STATE_H_

#include "LitRendererNoLightsState.h"

namespace sre
{

class Shader;
class ShaderManager;
class AGraphicsWrapper;

class LitRendererLightsState : public LitRendererNoLightsState
{
private:
    void onSceneLoaded(ShaderManager *shaderManager, Shader *shader) override;
    void setupShaderValues(ShaderManager *shaderManager, class MeshComponent *mesh, Shader *shader) override;
    void preDraw(AGraphicsWrapper *graphicsWrapper) override;
    void postDraw(AGraphicsWrapper *graphicsWrapper) override;
};

} // namespace

#endif
