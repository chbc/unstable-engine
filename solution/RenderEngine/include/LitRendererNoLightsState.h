#pragma once

#include <cstdint>

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;

class LitRendererNoLightsState
{
private:
    virtual void onSceneLoaded(ShaderManager *shaderManager, uint32_t program);
    virtual void setupShaderValues(ShaderManager *shaderManager, class MeshComponent *mesh, uint32_t program);
    virtual void preDraw(AGraphicsWrapper *graphicsWrapper);
    virtual void postDraw(AGraphicsWrapper *graphicsWrapper);

friend class LitRendererComponent;
};

} // namespace
