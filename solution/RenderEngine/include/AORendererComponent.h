#ifndef _AO_RENDERER_COMPONENT_H_
#define _AO_RENDERER_COMPONENT_H_

#include "DiffuseRendererComponent.h"

namespace sre
{

class AORendererComponent : public DiffuseRendererComponent
{
protected:
    AORendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(class Shader *shader) override;
    void setupShaderValues(MeshComponent *mesh, class Shader *shader) override;
    void preDraw(Shader* shader) override;
    void postDraw(Shader* shader) override;

    friend class MeshRenderer;
};

}  // namespace

#endif
