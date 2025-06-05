#include "LightManager.h"
#include "Entity.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "RefreshMeshesMessage.h"

namespace sre
{

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

    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->notify<RefreshMeshesMessage>();
}

void LightManager::addPointLight(PointLightComponent* item)
{
    this->pointLights.push_back(item);

    MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
    messagesManager->notify<RefreshMeshesMessage>();
}

void LightManager::removeDestroyedEntities()
{
    bool lightRemoved = CollectionsUtils::removeIfEntityIsDestroyed(this->directionalLights);
    lightRemoved |= CollectionsUtils::removeIfEntityIsDestroyed(this->pointLights);

    if (lightRemoved)
    {
        MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
        messagesManager->notify<RefreshMeshesMessage>();
    }
}

void LightManager::clean()
{
    this->directionalLights.clear();
    this->pointLights.clear();
}

} // namespace
