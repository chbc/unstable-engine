#ifndef _DIFFUSE_RENDERER_COMPONENT_H_
#define _DIFFUSE_RENDERER_COMPONENT_H_

#include "ColorRendererComponent.h"

namespace sre
{

class DiffuseRendererComponent : public ColorRendererComponent
{
protected:
    uint32_t textureId;
    int textureLocation;

protected:
    DiffuseRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    virtual void onLoadShader(Shader *shader) override;
    virtual void setupShaderVariables(MeshComponent *mesh, Shader *shader) override;
    virtual void preDraw() override;
    virtual void postDraw() override;

friend class Renderer;
};

} // namespace

#endif
