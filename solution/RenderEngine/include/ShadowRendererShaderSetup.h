#include "BaseRendererShaderSetup.h"

namespace sre
{

class ShadowRendererShaderSetup : public BaseRendererShaderSetup
{
protected:
    class LightManager *lightManager;

private:
    const char *DIRECTIONAL_LIGHT_SPACE_FORMAT  = "directionalLightSpaceMatrix[%d]";
	const uint32_t MAX_LIGHTS = 4;

protected:
    ShadowRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

    void onSceneLoaded(uint32_t program) override;
    void setupShaderValues(uint32_t program) override;

friend class MeshRenderer;
};

} // namespace
