#include "ShadowRendererShaderSetup.h"
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/graphics/LightManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/core/multimedia/textures/EMaterialMap.h>

namespace sre
{

ShadowRendererShaderSetup::ShadowRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : BaseRendererShaderSetup(shaderManager, graphicsWrapper)
{ 
    this->lightManager = SingletonsManager::getInstance()->get<LightManager>();
}

void ShadowRendererShaderSetup::onSceneLoaded(Shader *shader)
{
    char variable[32];
    for (uint32_t i = 0; i < this->lightManager->directionalLights.size(); i++)
    {
        sprintf_s(variable, DIRECTIONAL_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);

        sprintf_s(variable, DIRECTIONAL_LIGHT_SPACE_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);
    }

    for (uint32_t i = 0; i < this->lightManager->pointLights.size(); i++)
    {
        sprintf_s(variable, POINT_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);
    }
}

void ShadowRendererShaderSetup::setupShaderValues(Shader *shader)
{
    char variable[32];

    for (uint32_t i = 0; i < this->lightManager->directionalLights.size(); i++)
    {
        DirectionalLightComponent *light = this->lightManager->directionalLights[i];

        this->graphicsWrapper->activateShadowMapTexture(light->shadowData->textureId, light->shadowData->textureUnit);

        sprintf_s(variable, DIRECTIONAL_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setInt(shader, variable, light->shadowData->textureUnit);

        sprintf_s(variable, DIRECTIONAL_LIGHT_SPACE_FORMAT, i);
        this->shaderManager->setMat4(shader, variable, &light->lightSpaceMatrix[0][0]);
    }

    for (uint32_t i = 0; i < this->lightManager->pointLights.size(); i++)
    {
        PointLightComponent *light = this->lightManager->pointLights[i];
        this->graphicsWrapper->activateShadowMapTexture(light->shadowData->textureId, light->shadowData->textureUnit, true);

        sprintf_s(variable, POINT_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setInt(shader, variable, light->shadowData->textureUnit);
    }
}

} // namespace
