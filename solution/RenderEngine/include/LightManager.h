#pragma once

#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "ASingleton.h"
#include "LightsUBO.h"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace sre
{

class Entity;

class LightManager : public ASingleton
{
private:
    std::vector<DirectionalLightComponent *> directionalLights;
    std::vector<PointLightComponent *> pointLights;
    glm::vec3 ambientLightColor{ 0.15f };
	class AGraphicsWrapper* graphicsWrapper{ nullptr };
    LightsUBO lightsUBO;
	uint32_t ubo{ 0 };

public:
    void setAmbientLightColor(const glm::vec3 &ambientLightColor);
    bool hasAnyLight();
    bool hasAnyShadowCaster();

protected:
    void init() override;

private:
    void addDirectionalLight(DirectionalLightComponent* item);
    void addPointLight(PointLightComponent* item);
	void updateUniformBuffer();
    void removeDestroyedEntities();
    void cleanUp();

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
