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

    uint32_t depthMapFBO;
    class Shader *depthShader;
    std::vector<glm::mat4> shadowMatrices;
    float farPlane;
    const char *SHADOW_MATRICES_FORMAT = "shadowMatrices[%d]";

    std::vector<class MeshComponent *> items;

private:
    ShadowRenderer();

    void onSceneLoaded();
    void addItem(MeshComponent *item);
    void render();
    void removeDestroyedEntities();

friend class RenderManager;
};

} // namespace

#endif
