#include "LightManager.h"
#include "Entity.h"
#include <experimental/vector>

namespace sre
{

LightManager::LightManager()
{
    this->ambientLightColor = glm::vec3(0.125f, 0.125f, 0.125f);
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
    DirectionalLightComponent *newLight = entity->addComponent<DirectionalLightComponent>();
    this->directionalLights.push_back(newLight);

    return newLight;
}

PointLightComponent *LightManager::addPointLight(Entity *entity)
{
    PointLightComponent *newLight = entity->addComponent<PointLightComponent>();
    this->pointLights.push_back(newLight);

    return newLight;
}

void LightManager::removeDestroyedEntities()
{
    std::experimental::erase_if
    (
        this->directionalLights, 
        [](DirectionalLightComponent *item) { return !item->getEntity()->isAlive(); }
    );

    std::experimental::erase_if
    (
        this->pointLights,
        [](PointLightComponent *item) { return !item->getEntity()->isAlive(); }
    );
}

} // namespace
