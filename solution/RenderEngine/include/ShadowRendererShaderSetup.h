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

    void onSceneLoaded(uint32_t program) override;
    void setupShaderValues(uint32_t program) override;

friend class MeshRenderer;
};

} // namespace
