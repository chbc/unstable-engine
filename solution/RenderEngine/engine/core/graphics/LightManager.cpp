#include "LightManager.h"

#include <engine/entities/Entity.h>
#include <experimental/vector>

namespace sre
{

LightManager::LightManager()
{
    this->ambientLightColor = glm::vec3(0.25f, 0.25f, 0.25f);
}

void LightManager::setAmbientLightColor(const glm::vec3 &ambientLightColor)
{
    this->ambientLightColor = ambientLightColor;
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
