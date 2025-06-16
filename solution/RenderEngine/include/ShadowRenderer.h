#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace sre
{

class ShadowRenderer
{
private:
    class ShaderManager* shaderManager;
    class AGraphicsWrapper* graphicsWrapper;
    class LightManager* lightManager;
    class TextureCreator* textureCreator;

    uint32_t pointLightDepthProgram;
    uint32_t directionalLightDepthProgram;

    glm::mat4 shadowMatrices[6];
    const char *POINT_SHADOW_MATRICES_FORMAT = "pointShadowMatrices[%d]";

    std::vector<class MeshComponent *> items;

private:
    void init();
    void setupPointLightShader();
    void setupDirectionalLightShader();
    void addItem(MeshComponent *item);
    void render();
    void renderPointLightShadows();
    void renderDirectionalLightShadows();
    void removeDestroyedEntities();
    void updateShadowMatrices(const glm::vec3 &lightPosition, float range);

friend class RenderManager;
};

} // namespace
