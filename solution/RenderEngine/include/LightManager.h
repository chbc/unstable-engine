#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "ASingleton.h"
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

public:
    void setAmbientLightColor(const glm::vec3 &ambientLightColor);
    bool hasAnyLight();
    bool hasAnyShadowCaster();

private:
    LightManager();
    
    void addDirectionalLight(DirectionalLightComponent* item);
    void addPointLight(PointLightComponent* item);

    void removeDestroyedEntities();

friend class RenderManager;
friend class SingletonsManager;
friend class MeshRenderer;
friend class LightRendererShaderSetup;
friend class ShadowRendererShaderSetup;
friend class ShadowRenderer;
friend class DirectionalLightComponent;
friend class PointLightComponent;
};

} // namespace

#endif
