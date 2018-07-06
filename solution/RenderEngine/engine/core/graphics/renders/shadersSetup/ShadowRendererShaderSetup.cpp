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
    for (uint32_t i = 0; i < this->lightManager->pointLights.size(); i++)
    {
        sprintf_s(variable, POINT_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);
    }

    for (uint32_t i = 0; i < this->lightManager->directionalLights.size(); i++)
    {
        sprintf_s(variable, DIRECTIONAL_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);

        sprintf_s(variable, DIRECTIONAL_LIGHT_SPACE_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);
    }
}

void ShadowRendererShaderSetup::setupShaderValues(Shader *shader)
{
    // ### NAO VAI FUNCIONAR COM OS 2
    // COLOCAR TEXTURA COMO ATRIBUTO DAS LUZES
    char variable[32];
    for (uint32_t i = 0; i < this->lightManager->pointLights.size(); i++)
    {
        PointLightComponent *pointLight = this->lightManager->pointLights[i];
        this->graphicsWrapper->activateShadowMapTexture(pointLight->depthMap, EMaterialMap::SHADOW + i, true);

        sprintf_s(variable, POINT_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setInt(shader, variable, EMaterialMap::SHADOW + i);
    }

    for (uint32_t i = 0; i < this->lightManager->directionalLights.size(); i++)
    {
        DirectionalLightComponent *light = this->lightManager->directionalLights[i];

        this->graphicsWrapper->activateShadowMapTexture(light->depthMap, EMaterialMap::SHADOW + i);

        sprintf_s(variable, DIRECTIONAL_SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setInt(shader, variable, EMaterialMap::SHADOW + i);

        sprintf_s(variable, DIRECTIONAL_LIGHT_SPACE_FORMAT, i);
        this->shaderManager->setMat4(shader, ShaderVariables::LIGHT_SPACE_MATRIX, &light->lightSpaceMatrix[0][0]);
    }
}

} // namespace
