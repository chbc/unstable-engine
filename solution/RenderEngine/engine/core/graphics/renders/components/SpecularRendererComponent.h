#ifndef _SPECULAR_RENDERER_COMPONENT_H_
#define _SPECULAR_RENDERER_COMPONENT_H_

#include "DiffuseRendererComponent.h"

namespace sre
{

class SpecularRendererComponent : public DiffuseRendererComponent
{
protected:
    SpecularRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(class Shader *shader) override;
    void setupShaderValues(class MeshComponent *mesh, class Shader *shader) override;
    void preDraw() override;
    void postDraw() override;

    friend class Renderer;
};
} // namespace

#endif
