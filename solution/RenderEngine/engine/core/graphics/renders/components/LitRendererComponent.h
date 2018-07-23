#ifndef _LIT_COLOR_RENDERER_COMPONENT_H_
#define _LIT_COLOR_RENDERER_COMPONENT_H_

#include "ColorRendererComponent.h"

namespace sre
{

class LitRendererComponent : public ColorRendererComponent
{
protected:
    LitRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    virtual void onSceneLoaded(Shader *shader) override;
    virtual void setupShaderValues(class MeshComponent *mesh, Shader *shader) override;
    virtual void preDraw() override;
    virtual void postDraw() override;

    friend class Renderer;
};

} // namespace

#endif
