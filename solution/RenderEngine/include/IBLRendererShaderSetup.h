#pragma once

#include "BaseRendererShaderSetup.h"

namespace sre
{

class IBLRendererShaderSetup : public BaseRendererShaderSetup
{
protected:
    class LightManager *lightManager;

protected:
    IBLRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(uint32_t program) override;
    void setupShaderValues(uint32_t program) override;

friend class MeshRenderer;
};

} // namespace
