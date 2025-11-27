#pragma once

#include "ABaseRenderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace sre
{

class ShadowRenderer : public ABaseRenderer
{
private:
    class LightManager* lightManager;
    class TextureCreator* textureCreator;

    uint32_t pointLightDepthProgram;
    uint32_t directionalLightDepthProgram;

    glm::mat4 shadowMatrices[6];
    const char *POINT_SHADOW_MATRICES_FORMAT = "pointShadowMatrices[%d]";

private:
    ShadowRenderer(ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWrapper);

    void init();
    void setupPointLightShader();
    void setupDirectionalLightShader();
    void render();
    void renderPointLightShadows();
    void renderDirectionalLightShadows();
    void updateShadowMatrices(const glm::vec3 &lightPosition, float range);

friend class RenderManager;
};

} // namespace
