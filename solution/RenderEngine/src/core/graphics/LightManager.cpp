#include "LightManager.h"
#include "Entity.h"
#include "CollectionsUtils.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "AssetsManager.h"
#include "Texture.h"
#include "MessagesManager.h"
#include "TextureCreator.h"

namespace sre
{

void LightManager::init()
{
	this->graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
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
    int maxDirectionalLights = static_cast<int>(this->directionalLights.size());
    this->lightsUBO.maxDirectionalLights = maxDirectionalLights;

    for (int i = 0; i < maxDirectionalLights; ++i)
    {
        DirectionalLightComponent* light = this->directionalLights[i];
        this->lightsUBO.directionalLights[i].direction = glm::vec4{ light->getTransform()->getForward(), 0.0f };
        this->lightsUBO.directionalLights[i].color = glm::vec4{ light->getColor(), 1.0f };

		light->updateShadowTextureUnit(ETextureMap::SHADOWS + i);
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

		light->updateShadowTextureUnit(ETextureMap::SHADOWS + MAX_GROUP_LIGHTS + i);
    }

    this->updateUniformBuffer();
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
    bool lightRemoved = CollectionsUtils::removeComponentIfEntityIsDestroyed(this->directionalLights);
    if (lightRemoved)
    {
        this->updateDirectionalLightsUBO();
    }

    lightRemoved = CollectionsUtils::removeComponentIfEntityIsDestroyed(this->pointLights);
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
