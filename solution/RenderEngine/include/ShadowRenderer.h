#ifndef _SHADOW_RENDERER_H_
#define _SHADOW_RENDERER_H_

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace sre
{

class ShadowRenderer
{
private:
    class ShaderManager *shaderManager;
    class AGraphicsWrapper *graphicsWrapper;
    class LightManager *lightManager;

    class Shader *pointLightDepthShader;
    class Shader *directionalLightDepthShader;

    glm::mat4 shadowMatrices[6];
    const char *POINT_SHADOW_MATRICES_FORMAT = "pointShadowMatrices[%d]";

    std::vector<class MeshComponent *> items;

private:
    void init();
    void setupPointLightShader(class TextureManager *textureManager);
    void setupDirectionalLightShader(class TextureManager *textureManager);
    void addItem(MeshComponent *item);
    void render();
    void renderPointLightShadows();
    void renderDirectionalLightShadows();
    void removeDestroyedEntities();
    void updateShadowMatrices(const glm::vec3 &lightPosition, float range);

friend class RenderManager;
};

} // namespace

#endif
