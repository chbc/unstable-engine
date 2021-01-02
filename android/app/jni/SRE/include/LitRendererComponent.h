#ifndef _LIT_COLOR_RENDERER_COMPONENT_H_
#define _LIT_COLOR_RENDERER_COMPONENT_H_

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
    LitRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper, bool hasLight);

    virtual void onSceneLoaded(Shader *shader) override;
    virtual void setupShaderValues(class MeshComponent *mesh, Shader *shader) override;
    virtual void preDraw(Shader* shader) override;
    virtual void postDraw(Shader* shader) override;

    friend class MeshRenderer;
};

} // namespace

#endif
