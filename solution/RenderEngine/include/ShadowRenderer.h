#pragma once

#include "memory_aliases.h"
#include "ABaseRenderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace sre
{

class ShadowRenderer : public ABaseRenderer
{
private:
    glm::mat4 shadowMatrices[6];
    const char *POINT_SHADOW_MATRICES_FORMAT = "pointShadowMatrices[%d]";
    class LightManager* lightManager{ nullptr };

    uint32_t pointLightDepthProgram{ 0 };
    uint32_t directionalLightDepthProgram{ 0 };

private:
    ShadowRenderer(ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWrapper);

    void init();
    void setupLigths();
    void setupPointLightShader();
    void setupDirectionalLightShader();
    void render();
    void renderPointLightShadows();
    void renderDirectionalLightShadows();
    void updateShadowMatrices(const glm::vec3 &lightPosition, float range);

friend class RenderManager;
};

} // namespace
