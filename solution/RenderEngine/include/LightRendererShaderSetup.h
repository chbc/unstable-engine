#ifndef _LIGHT_RENDERER_SHADER_SETUP_H_
#define _LIGHT_RENDERER_SHADER_SETUP_H_

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

    void onSceneLoaded(Shader *shader) override;
    void setupShaderValues(Shader *shader) override;

private:
    void setupDirectionalsVariablesLocations(Shader *shader);
    void setupPointsVariablesLocations(Shader *shader);

    void setupDirectionalValues(Shader *shader);
    void setupPointValues(Shader *shader);

friend class MeshRenderer;
};

} // namespace

#endif
