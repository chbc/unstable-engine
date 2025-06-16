#pragma once

#include "DiffuseRendererComponent.h"

namespace sre
{

class AORendererComponent : public DiffuseRendererComponent
{
protected:
    AORendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(uint32_t program) override;
    void setupShaderValues(MeshComponent *mesh, uint32_t program) override;
    void preDraw(uint32_t program) override;
    void postDraw(uint32_t program) override;

    friend class MeshRenderer;
};

}  // namespace
