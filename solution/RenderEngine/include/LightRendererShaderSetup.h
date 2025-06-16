#pragma once

#include "ShadowRendererShaderSetup.h"

namespace sre
{

class LightRendererShaderSetup : public BaseRendererShaderSetup
{
protected:
    class LightManager *lightManager;

private:
    const char *DIRECTIONAL_DIRECTION_FORMAT = "directionalLights[%d].direction";
    const char *DIRECTIONAL_COLOR_FORMAT = "directionalLights[%d].color";

    const char *POINT_POSITION_FORMAT = "pointLights[%d].position";
    const char *POINT_COLOR_FORMAT = "pointLights[%d].color";
    const char *POINT_RANGE_FORMAT = "pointLights[%d].range";
    const char *POINT_INTENSITY_FORMAT = "pointLights[%d].intensity";

protected:
    LightRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(uint32_t program) override;
    void setupShaderValues(uint32_t program) override;

private:
    void setupDirectionalsVariablesLocations(uint32_t program);
    void setupPointsVariablesLocations(uint32_t program);

    void setupDirectionalValues(uint32_t program);
    void setupPointValues(uint32_t program);

friend class MeshRenderer;
};

} // namespace
