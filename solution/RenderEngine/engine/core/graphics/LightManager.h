#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>
#include <engine/core/singletonsManager/ASingleton.h>

#include <vector>

namespace sre
{

class Entity;
class ShaderManager;
class Shader;
class MeshComponent;

/*!
    Class to manage low level lighting.
*/
class LightManager : public ASingleton
{
private:
    std::vector<DirectionalLightComponent *> directionalLights;
    std::vector<PointLightComponent *> pointLights;

    glm::vec3 ambientLightColor;

    // ### SOMBRA
    class ShaderManager *shaderManager;
    class AGraphicsWrapper *graphicsWrapper;

    uint32_t depthMap;
    uint32_t depthMapFBO;
    Shader *depthShader;

    std::vector<MeshComponent *> meshes;

public:
    void setAmbientLightColor(const glm::vec3 &ambientLightColor);

private:
    LightManager();

    void init() override;
    void onSceneLoaded();
    void generateDepthMap();

    void addShadowCaster(MeshComponent *mesh);

    DirectionalLightComponent *addDirectionalLight(Entity *entity);
    PointLightComponent *addPointLight(Entity *entity);

    void removeDestroyedEntities();

friend class RenderManager;
friend class SingletonsManager;
friend class LightRendererShaderSetup;
friend class ShadowRendererShaderSetup;
};

} // namespace

#endif
