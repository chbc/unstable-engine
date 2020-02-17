#ifndef _LIT_RENDERER_NO_LIGHTS_STATE_H_
#define _LIT_RENDERER_NO_LIGHTS_STATE_H_

namespace sre
{

class Shader;
class ShaderManager;
class AGraphicsWrapper;

class LitRendererNoLightsState
{
private:
    virtual void onSceneLoaded(ShaderManager *shaderManager, Shader *shader);
    virtual void setupShaderValues(ShaderManager *shaderManager, class MeshComponent *mesh, Shader *shader);
    virtual void preDraw(AGraphicsWrapper *graphicsWrapper);
    virtual void postDraw(AGraphicsWrapper *graphicsWrapper);

friend class LitRendererComponent;
};

} // namespace


#endif
