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

void LightManager::addDirectionalLight(DirectionalLightComponent* item)
{
    this->directionalLights.push_back(item);
}

void LightManager::addPointLight(PointLightComponent* item)
{
    this->pointLights.push_back(item);
}

void LightManager::removeDestroyedEntities()
{
    CollectionsUtils::removeIfEntityIsDestroyed(this->directionalLights);
    CollectionsUtils::removeIfEntityIsDestroyed(this->pointLights);
}

} // namespace
