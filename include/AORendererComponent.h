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
    void preDraw() override;
    void postDraw() override;

    friend class Renderer;
};

}  // namespace

#endif
