#pragma once

#include "ShadowRendererShaderSetup.h"

namespace sre
{

class LightRendererShaderSetup : public BaseRendererShaderSetup
{
protected:
    class LightManager *lightManager;

protected:
    LightRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(uint32_t program) override;
    void setupShaderValues(uint32_t program) override;

friend class MeshRenderer;
};

} // namespace
