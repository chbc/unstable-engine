#include "LightManager.h"
#include "Entity.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"

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

void LightManager::init()
{
	this->graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
}

void LightManager::addDirectionalLight(DirectionalLightComponent* item)
{
    this->directionalLights.push_back(item);
	this->updateDirectionalLightsUBO();
}

void LightManager::addPointLight(PointLightComponent* item)
{
    this->pointLights.push_back(item);
	this->updatePointLightsUBO();
}

void LightManager::updateDirectionalLightsUBO()
{
    int maxDirectionalLights = static_cast<int>(this->directionalLights.size());
    this->lightsUBO.maxDirectionalLights = maxDirectionalLights;

    for (int i = 0; i < maxDirectionalLights; ++i)
    {
        DirectionalLightComponent* light = this->directionalLights[i];
        this->lightsUBO.directionalLights[i].direction = glm::vec4{ light->getTransform()->getForward(), 0.0f };
        this->lightsUBO.directionalLights[i].color = glm::vec4{ light->getColor(), 1.0f };
    }

    this->updateUniformBuffer();
}

void LightManager::updatePointLightsUBO()
{
    int maxPointLights = static_cast<int>(this->pointLights.size());
    this->lightsUBO.maxPointLights = maxPointLights;

    for (int i = 0; i < maxPointLights; ++i)
    {
        PointLightComponent* light = this->pointLights[i];
        this->lightsUBO.pointLights[i].position = glm::vec4{ light->getTransform()->getInternalMatrixPosition(), 0.0f };
        this->lightsUBO.pointLights[i].color = glm::vec4{ light->getColor(), 1.0f };
        this->lightsUBO.pointLights[i].rangeAndIntensity.x = light->getRange();
        this->lightsUBO.pointLights[i].rangeAndIntensity.y = light->getIntensity();
    }

    this->updateUniformBuffer();
}

void LightManager::updateUniformBuffer()
{
    size_t dataSize = sizeof(LightsUBO);
    if (this->ubo == 0)
    {
        this->graphicsWrapper->createUniformBuffer(this->ubo, dataSize, &this->lightsUBO);
    }
    else
    {
        this->graphicsWrapper->updateUniformBuffer(this->ubo, dataSize, &this->lightsUBO);
    }
}

void LightManager::removeDestroyedEntities()
{
    bool lightRemoved = CollectionsUtils::removeIfEntityIsDestroyed(this->directionalLights);
    if (lightRemoved)
    {
        this->updateDirectionalLightsUBO();
    }

    lightRemoved = CollectionsUtils::removeIfEntityIsDestroyed(this->pointLights);
    if (lightRemoved)
    {
        this->updatePointLightsUBO();
	}
}

void LightManager::cleanUp()
{
    this->directionalLights.clear();
    this->pointLights.clear();

    if (this->ubo != 0)
    {
        this->graphicsWrapper->deleteUniformBuffer(this->ubo);
		this->ubo = 0;
    }
}

} // namespace
