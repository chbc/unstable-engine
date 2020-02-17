#ifndef _SHADOW_RENDERER_SHADER_SETUP_H_
#define _SHADOW_RENDERER_SHADER_SETUP_H_

#include "BaseRendererShaderSetup.h"

namespace sre
{

class ShadowRendererShaderSetup : public BaseRendererShaderSetup
{
protected:
    class LightManager *lightManager;

private:
    const char *POINT_SHADOW_MAPS_FORMAT        = "pointShadowMaps[%d]";
    const char *DIRECTIONAL_SHADOW_MAPS_FORMAT  = "directionalShadowMaps[%d]";
    const char *DIRECTIONAL_LIGHT_SPACE_FORMAT  = "directionalLightSpaceMatrix[%d]";

protected:
    ShadowRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(Shader *shader) override;
    void setupShaderValues(Shader *shader, const glm::vec3& cameraPosition) override;

friend class Renderer;
};

} // namespace

#endif
