#ifndef _LIGHT_RENDERER_SHADER_SETUP_H_
#define _LIGHT_RENDERER_SHADER_SETUP_H_

#include "ShadowRendererShaderSetup.h"

namespace sre
{

class LightRendererShaderSetup : public ShadowRendererShaderSetup
{
private:
    const char *DIRECTIONAL_DIRECTION_FORMAT = "lights.directionalLights[%d].direction";
    const char *DIRECTIONAL_COLOR_FORMAT = "lights.directionalLights[%d].color";

    const char *POINT_POSITION_FORMAT = "lights.pointLights[%d].position";
    const char *POINT_COLOR_FORMAT = "lights.pointLights[%d].color";
    const char *POINT_RANGE_FORMAT = "lights.pointLights[%d].range";
    const char *POINT_INTENSITY_FORMAT = "lights.pointLights[%d].intensity";

protected:
    LightRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(Shader *shader) override;
    void setupShaderValues(Shader *shader) override;

private:
    void setupDirectionalsVariablesLocations(Shader *shader);
    void setupPointsVariablesLocations(Shader *shader);

    void setupDirectionalValues(Shader *shader);
    void setupPointValues(Shader *shader);

friend class Renderer;
};

} // namespace

#endif
