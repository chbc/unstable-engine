#ifndef _OUTLINE_RENDERER_COMPONENT_H_
#define _OUTLINE_RENDERER_COMPONENT_H_

#include "ColorRendererComponent.h"

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;
class Shader;

class OutlineRendererComponent : public ColorRendererComponent
{

protected:
    OutlineRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    virtual void onSceneLoaded(Shader *shader) override;
    virtual void setupShaderValues(class MeshComponent *mesh, Shader *shader) override;
    virtual void preDraw() override;
    virtual void postDraw() override;

friend class MeshRenderer;
};

} // namespace

#endif
