#include "LightManager.h"
#include "Entity.h"
#include "CollectionsUtils.h"

namespace sre
{

LightManager::LightManager()
{
    this->ambientLightColor = glm::vec3(0.15f, 0.15f, 0.15f);
}

void LightManager::setAmbientLightColor(const glm::vec3 &ambientLightColor)
{
    this->ambientLightColor = ambientLightColor;
}

bool LightManager::hasAnyLight()
{
    return (!this->directionalLights.empty() || !this->pointLights.empty());
}

bool LightManager::hasAnyShadowCaster()
{
    return
    (
        (!this->directionalLights.empty() && this->directionalLights[0]->hasShadowData()) ||
        (!this->pointLights.empty() && this->pointLights[0]->hasShadowData())
    );
}

DirectionalLightComponent *LightManager::addDirectionalLight(Entity *entity)
{
    DirectionalLightComponent *newLight = entity->getComponent<DirectionalLightComponent>();
    this->directionalLights.push_back(newLight);

    return newLight;
}

PointLightComponent *LightManager::addPointLight(Entity *entity)
{
    PointLightComponent *newLight = entity->getComponent<PointLightComponent>();
    this->pointLights.push_back(newLight);

    return newLight;
}

void LightManager::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->directionalLights);
    CollectionsUtils::removeIfEntityIsDestroyed(this->pointLights);
}

} // namespace
