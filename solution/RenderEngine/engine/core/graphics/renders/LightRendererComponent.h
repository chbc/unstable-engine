#ifndef _LIGHT_RENDERER_COMPONENT_H_
#define _LIGHT_RENDERER_COMPONENT_H_

#include "ColorRendererComponent.h"

namespace sre
{

class LightRendererComponent : public ColorRendererComponent
{
private:
    class LightManager *lightManager;

    const char *DIRECTIONAL_DIRECTION_FORMAT = "lights.directionalLights[%d].direction";
    const char *DIRECTIONAL_COLOR_FORMAT = "lights.directionalLights[%d].color";

    const char *POINT_POSITION_FORMAT = "lights.pointLights[%d].position";
    const char *POINT_COLOR_FORMAT = "lights.pointLights[%d].color";
    const char *POINT_RANGE_FORMAT = "lights.pointLights[%d].range";
    const char *POINT_INTENSITY_FORMAT = "lights.pointLights[%d].intensity";

protected:
    LightRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onLoadShader(Shader *shader) override;
    void setupShaderVariables(MeshComponent *mesh, Shader *shader) override;

private:
    void setupDirectionalsVariablesLocations(Shader *shader);
    void setupPointsVariablesLocations(Shader *shader);

    void setupDirectionalValues(Shader *shader);
    void setupPointValues(Shader *shader);

friend class Renderer;
};

} // namespace

#endif
