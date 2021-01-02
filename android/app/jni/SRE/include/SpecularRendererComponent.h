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
    void preDraw(Shader* shader) override;
    void postDraw(Shader* shader) override;

    friend class MeshRenderer;
};
} // namespace

#endif
