#include "LightManager.h"
#include "Entity.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "AssetsManager.h"
#include "Texture.h"
#include "MessagesManager.h"
#include "TextureCreator.h"
#include "GlobalUniformsManager.h"
#include "LightsUBO.h"
#include "MessagesManager.h"
#include "EntityDestructionMessage.h"

namespace sre
{

void LightManager::init()
{
	this->graphicsWrapper = SingletonsManager::Get<AGraphicsWrapper>();

    this->entitiesDestroyedAction = new Action{ [&](void* message) { this->onEntityDestroyed(message); } };
	MessagesManager* messagesManager = SingletonsManager::Get<MessagesManager>();
    messagesManager->addListener<EntityDestroyedMessage>(this->entitiesDestroyedAction);
}

size_t LightManager::getDirectionalLightsCount() const
{
	return this->directionalLights.size();
}

size_t LightManager::getPointLightsCount() const
{
    return this->pointLights.size();
}

void LightManager::addDirectionalLight(DirectionalLightComponent* item)
{
	this->setupShadowData(item, false);
    this->directionalLights.push_back(item);

	this->updateDirectionalLightsUBO();
}

void LightManager::addPointLight(PointLightComponent* item)
{
	this->setupShadowData(item, true);
    this->pointLights.push_back(item);

	this->updatePointLightsUBO();
}

void LightManager::updateDirectionalLightsUBO()
{
	LightsUBO& lightsUBO = SingletonsManager::Get<GlobalUniformsManager>()->editLightsUBO();

    int maxDirectionalLights = static_cast<int>(this->directionalLights.size());
    lightsUBO .maxDirectionalLights = maxDirectionalLights;

    for (int i = 0; i < maxDirectionalLights; ++i)
    {
        DirectionalLightComponent* light = this->directionalLights[i];
        lightsUBO.directionalLights[i].direction = glm::vec4{ light->getTransform()->getForward(), 0.0f };
        lightsUBO.directionalLights[i].color = glm::vec4{ light->getColor(), 1.0f };

        light->updateShadowTextureUnit(ETextureMap::SHADOWS + i);
    }
}

void LightManager::updatePointLightsUBO()
{
    LightsUBO& lightsUBO = SingletonsManager::Get<GlobalUniformsManager>()->editLightsUBO();

    int maxPointLights = static_cast<int>(this->pointLights.size());
    lightsUBO.maxPointLights = maxPointLights;

    for (int i = 0; i < maxPointLights; ++i)
    {
        PointLightComponent* light = this->pointLights[i];
        lightsUBO.pointLights[i].position = glm::vec4{ light->getTransform()->getInternalMatrixPosition(), 0.0f };
        lightsUBO.pointLights[i].color = glm::vec4{ light->getColor(), 1.0f };
        lightsUBO.pointLights[i].rangeAndIntensity.x = light->getRange();
        lightsUBO.pointLights[i].rangeAndIntensity.y = light->getIntensity();

        light->updateShadowTextureUnit(ETextureMap::SHADOWS + MAX_GROUP_LIGHTS + i);
    }
}

void LightManager::setupShadowData(ALightComponent* lightComponent, bool useCubemap)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    TextureCreator* textureCreator = singletonsManager->get<TextureCreator>();
    AGraphicsWrapper* graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();

    Texture* texture{ nullptr };
	uint32_t fbo{ 0 };
    if (useCubemap)
    {
        texture = textureCreator->createPointShadowTexture(1024, 1024, fbo);
    }
    else
    {
        texture = textureCreator->createDirectionalShadowTexture(1024, 1024, fbo);
    }

    lightComponent->shadowData = UPTR<ShadowData>(new ShadowData{ fbo, texture->getId(), texture->getUnit() });
}

void LightManager::loadIBL(std::unordered_map<ETextureMap::Type, Texture*>& texturesMap)
{
    Texture* irradiance = texturesMap[ETextureMap::IBL_IRRADIANCE];
    Texture* prefilter = texturesMap[ETextureMap::IBL_PREFILTER];
    Texture* brdfLUT = texturesMap[ETextureMap::IBL_BRDF_LUT];

    iblData.irradianceMap = irradiance->getId();
    iblData.prefilterMap = prefilter->getId();
    iblData.brdfLUTMap = brdfLUT->getId();
    iblData.loaded = true;
}

void LightManager::clearIBLData()
{
    iblData.irradianceMap = 0;
    iblData.prefilterMap = 0;
    iblData.brdfLUTMap = 0;
	iblData.loaded = false;
}

void LightManager::onEntityDestroyed(void* data)
{
    MessagesManager* messagesManager = SingletonsManager::Get<MessagesManager>();
    EntityDestroyedMessage* message = static_cast<EntityDestroyedMessage*>(data);
    Entity* entity = message->entity;
    if (entity->hasComponent<DirectionalLightComponent>())
    {
		DirectionalLightComponent* component = entity->getComponent<DirectionalLightComponent>();
		auto it = std::find(this->directionalLights.begin(), this->directionalLights.end(), component);
        if (it != this->directionalLights.end())
        {
            this->directionalLights.erase(it);
        }
    }
    else if (entity->hasComponent<PointLightComponent>())
    {
        PointLightComponent* component = entity->getComponent<PointLightComponent>();
        auto it = std::find(this->pointLights.begin(), this->pointLights.end(), component);
        if (it != this->pointLights.end())
        {
            this->pointLights.erase(it);
        }
	}
}

void LightManager::cleanUp()
{
    this->directionalLights.clear();
    this->pointLights.clear();
}

} // namespace
