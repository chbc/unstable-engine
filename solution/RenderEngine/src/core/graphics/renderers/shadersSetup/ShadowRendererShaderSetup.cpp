#include "ShadowRendererShaderSetup.h"
#include "ShaderManager.h"
#include "LightManager.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "ETextureMap.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sre
{

ShadowRendererShaderSetup::ShadowRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : BaseRendererShaderSetup(shaderManager, graphicsWrapper)
{ 
    this->lightManager = SingletonsManager::getInstance()->get<LightManager>();
}

void ShadowRendererShaderSetup::onSceneLoaded(uint32_t program)
{
    char variable[32];
    for (uint32_t i = 0; i < this->lightManager->directionalLights.size(); i++)
    {
        std::sprintf(variable, DIRECTIONAL_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setupUniformLocation(program, variable);

        std::sprintf(variable, DIRECTIONAL_LIGHT_SPACE_FORMAT, i);
        this->shaderManager->setupUniformLocation(program, variable);
    }

    for (uint32_t i = 0; i < this->lightManager->pointLights.size(); i++)
    {
        std::sprintf(variable, POINT_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setupUniformLocation(program, variable);
    }
}

void ShadowRendererShaderSetup::setupShaderValues(uint32_t program)
{
    char variable[32];

    for (uint32_t i = 0; i < this->lightManager->directionalLights.size(); i++)
    {
        DirectionalLightComponent *light = this->lightManager->directionalLights[i];

        this->graphicsWrapper->activateShadowMapTexture(light->shadowData->textureId, light->shadowData->textureUnit);

        std::sprintf(variable, DIRECTIONAL_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setInt(program, variable, light->shadowData->textureUnit);

        std::sprintf(variable, DIRECTIONAL_LIGHT_SPACE_FORMAT, i);
        this->shaderManager->setMat4(program, variable, &light->lightSpaceMatrix[0][0]);
    }

    for (uint32_t i = 0; i < this->lightManager->pointLights.size(); i++)
    {
        PointLightComponent *light = this->lightManager->pointLights[i];
        this->graphicsWrapper->activateShadowMapTexture(light->shadowData->textureId, light->shadowData->textureUnit, true);

        std::sprintf(variable, POINT_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setInt(program, variable, light->shadowData->textureUnit);
    }
}

} // namespace
