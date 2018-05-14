#ifndef _AO_RENDERER_COMPONENT_H_
#define _AO_RENDERER_COMPONENT_H_

#include "DiffuseRendererComponent.h"

namespace sre
{

class AORendererComponent : public DiffuseRendererComponent
{
protected:
    AORendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onLoadShader(class Shader *shader) override;
    void setupShaderVariables(MeshComponent *mesh, class Shader *shader) override;
    void preDraw() override;
    void postDraw() override;

    friend class Renderer;
};

}  // namespace

#endif
