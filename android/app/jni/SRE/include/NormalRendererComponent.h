#ifndef _NORMAL_RENDERER_COMPONENT_H_
#define _NORMAL_RENDERER_COMPONENT_H_

#include "DiffuseRendererComponent.h"

namespace sre
{

class NormalRendererComponent : public DiffuseRendererComponent
{
protected:
    NormalRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(class Shader *shader) override;
    void setupShaderValues(class MeshComponent *mesh, class Shader *shader) override;
    void preDraw() override;
    void postDraw() override;

friend class MeshRenderer;
};

} // namespace

#endif
