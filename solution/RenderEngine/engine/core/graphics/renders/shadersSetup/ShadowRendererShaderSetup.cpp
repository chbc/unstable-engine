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
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::FAR_PLANE);

    char variable[32];
    for (uint32_t i = 0; i < this->lightManager->pointLights.size(); i++)
    {
        sprintf_s(variable, SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);
    }
}

void ShadowRendererShaderSetup::setupShaderValues(Shader *shader)
{
    char variable[32];
    for (uint32_t i = 0; i < this->lightManager->pointLights.size(); i++)
    {
        sprintf_s(variable, SHADOW_MAPS_FORMAT, i);
        this->shaderManager->setInt(shader, variable, EMaterialMap::SHADOW + i);

        PointLightComponent *pointLight = this->lightManager->pointLights[i];
        this->graphicsWrapper->activateShadowMapTexture(pointLight->depthCubemap, EMaterialMap::SHADOW + i);
    }

    float farPlane = 50.0f;
    this->shaderManager->setFloat(shader, ShaderVariables::FAR_PLANE, farPlane);
}

} // namespace
