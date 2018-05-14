#ifndef _NORMAL_RENDERER_COMPONENT_H_
#define _NORMAL_RENDERER_COMPONENT_H_

#include "DiffuseRendererComponent.h"

namespace sre
{

class NormalRendererComponent : public DiffuseRendererComponent
{
protected:
    NormalRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onLoadShader(class Shader *shader) override;
    void setupShaderVariables(class MeshComponent *mesh, class Shader *shader) override;
    void preDraw() override;
    void postDraw() override;

friend class Renderer;
};

} // namespace

#endif
