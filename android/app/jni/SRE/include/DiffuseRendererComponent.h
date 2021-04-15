#ifndef _DIFFUSE_RENDERER_COMPONENT_H_
#define _DIFFUSE_RENDERER_COMPONENT_H_

#include <cstdint>

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

    virtual void onSceneLoaded(Shader *shader) override;
    virtual void setupShaderValues(MeshComponent *mesh, Shader *shader) override;
    virtual void preDraw(Shader* shader) override;
    virtual void postDraw(Shader* shader) override;

friend class MeshRenderer;
};

} // namespace

#endif
