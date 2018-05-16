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

/*!
    Class to manage low level lighting.
*/
class LightManager : public ASingleton
{
private:
    std::vector<DirectionalLightComponent *> directionalLights;
    std::vector<PointLightComponent *> pointLights;

    glm::vec3 ambientLightColor;

    int ambientLightColorLocation;

    const char *DIRECTIONAL_DIRECTION_FORMAT    = "lights.directionalLights[%d].direction";
    const char *DIRECTIONAL_COLOR_FORMAT        = "lights.directionalLights[%d].color";

    const char *POINT_POSITION_FORMAT   = "lights.pointLights[%d].position";
    const char *POINT_COLOR_FORMAT      = "lights.pointLights[%d].color";
    const char *POINT_RANGE_FORMAT      = "lights.pointLights[%d].range";
    const char *POINT_INTENSITY_FORMAT  = "lights.pointLights[%d].intensity";

public:
    void setAmbientLightColor(const glm::vec3 &ambientLightColor);

private:
    LightManager();

    DirectionalLightComponent *addDirectionalLight(Entity *entity);
    PointLightComponent *addPointLight(Entity *entity);

    void onSceneLoaded();

    void setupVariablesLocations(ShaderManager *shaderManager);
    void setupDirectionalsVariablesLocations(ShaderManager *shaderManager);
    void setupPointsVariablesLocations(ShaderManager *shaderManager);
    void setupValues(ShaderManager *shaderManager, Shader *shader);
    void setupDirectionalValues(ShaderManager *shaderManager, Shader *shader);
    void setupPointValues(ShaderManager *shaderManager, Shader *shader);

    void removeDestroyedEntities();

friend class RenderManager;
friend class SingletonsManager;
friend class Renderer;
};

} // namespace

#endif
