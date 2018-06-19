#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>
#include <engine/core/singletonsManager/ASingleton.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace sre
{

class Entity;

/*!
    Class to manage low level lighting.
*/
class LightManager : public ASingleton
{
private:
    std::vector<DirectionalLightComponent *> directionalLights;
    std::vector<PointLightComponent *> pointLights;

    glm::vec3 ambientLightColor;

    /* ### DIRECIONAL
    uint32_t depthMap;
    glm::mat4 lightSpaceMatrix;
    */

public:
    void setAmbientLightColor(const glm::vec3 &ambientLightColor);

private:
    LightManager();
    
    DirectionalLightComponent *addDirectionalLight(Entity *entity);
    PointLightComponent *addPointLight(Entity *entity);

    void removeDestroyedEntities();

friend class RenderManager;
friend class SingletonsManager;
friend class LightRendererShaderSetup;
friend class ShadowRendererShaderSetup;
friend class ShadowRenderer;
};

} // namespace

#endif
