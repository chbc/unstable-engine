#pragma once

#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "ASingleton.h"
#include "LightsUBO.h"
#include "IBLData.h"
#include "ETextureMap.h"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace sre
{

class Entity;
class Texture;

class LightManager : public ASingleton
{
private:
    std::vector<DirectionalLightComponent*> directionalLights;
    std::vector<PointLightComponent*> pointLights;
	class AGraphicsWrapper* graphicsWrapper{ nullptr };
    LightsUBO lightsUBO;
	uint32_t ubo{ 0 };
    IBLData iblData;

public:
    bool hasAnyShadowCaster();
    inline const IBLData& getIBLData() { return iblData; }

protected:
    void init() override;

private:
    void addDirectionalLight(DirectionalLightComponent* item);
    void addPointLight(PointLightComponent* item);
	void updateUniformBuffer();
    void updateDirectionalLightsUBO();
	void updatePointLightsUBO();
    void loadIBL(std::unordered_map<ETextureMap::Type, Texture*>& texturesMap);
    void clearIBLData();
    void removeDestroyedEntities();
    void cleanUp();

friend class RenderManager;
friend class SingletonsManager;
friend class MeshRenderer;
friend class LightRendererShaderSetup;
friend class ShadowRendererShaderSetup;
friend class ShadowRenderer;
friend class SkyboxRenderer;
friend class DirectionalLightComponent;
friend class PointLightComponent;
};

} // namespace
