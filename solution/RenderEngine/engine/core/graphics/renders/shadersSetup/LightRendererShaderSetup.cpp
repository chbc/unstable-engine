#include "LightRendererShaderSetup.h"
#include <engine/core/graphics/LightManager.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/entities/components/lights/PointLightComponent.h>

namespace sre
{

LightRendererShaderSetup::LightRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : ShadowRendererShaderSetup(shaderManager, graphicsWrapper)
{ }

void LightRendererShaderSetup::onSceneLoaded(Shader *shader)
{
    if (lightManager->directionalLights.size() > 0)
    {
        this->shaderManager->setupUniformLocation(shader, ShaderVariables::DIRECTIONAL_LIGHTS_COUNT);
        this->setupDirectionalsVariablesLocations(shader);
    }

    if (this->lightManager->pointLights.size() > 0)
    {
        shaderManager->setupUniformLocation(shader, ShaderVariables::POINT_LIGHTS_COUNT);
        this->setupPointsVariablesLocations(shader);
    }

    shaderManager->setupUniformLocation(shader, ShaderVariables::AMBIENT_LIGHT_COLOR);
}

void LightRendererShaderSetup::setupShaderValues(Shader *shader)
{
    if (this->lightManager->directionalLights.size() > 0)
        this->setupDirectionalValues(shader);

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointValues(shader);

    shaderManager->setVec3(shader, ShaderVariables::AMBIENT_LIGHT_COLOR, &this->lightManager->ambientLightColor[0]);
}

void LightRendererShaderSetup::setupDirectionalsVariablesLocations(Shader *shader)
{
    char variable[128];

    int count = this->lightManager->directionalLights.size();
    for (int i = 0; i < count; i++)
    {
        sprintf_s(variable, DIRECTIONAL_DIRECTION_FORMAT, i);
        shaderManager->setupUniformLocation(shader, variable);

        sprintf_s(variable, DIRECTIONAL_COLOR_FORMAT, i);
        shaderManager->setupUniformLocation(shader, variable);
    }
}

void LightRendererShaderSetup::setupPointsVariablesLocations(Shader *shader)
{
    char variable[128];

    int count = this->lightManager->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        sprintf_s(variable, POINT_POSITION_FORMAT, i);
        shaderManager->setupUniformLocation(shader, variable);

        sprintf_s(variable, POINT_COLOR_FORMAT, i);
        shaderManager->setupUniformLocation(shader, variable);

        sprintf_s(variable, POINT_RANGE_FORMAT, i);
        shaderManager->setupUniformLocation(shader, variable);

        sprintf_s(variable, POINT_INTENSITY_FORMAT, i);
        shaderManager->setupUniformLocation(shader, variable);
    }
}

void LightRendererShaderSetup::setupDirectionalValues(Shader *shader)
{
    char variable[100];

    DirectionalLightComponent *light = nullptr;
    int count = this->lightManager->directionalLights.size();
    for (int i = 0; i < count; i++)
    {
        light = this->lightManager->directionalLights[i];
        glm::vec3 direction = light->getDirection();
        glm::vec3 color = light->getColor();

        sprintf_s(variable, DIRECTIONAL_DIRECTION_FORMAT, i);
        shaderManager->setVec3(shader, variable, &direction[0]);

        sprintf_s(variable, DIRECTIONAL_COLOR_FORMAT, i);
        shaderManager->setVec3(shader, variable, &color[0]);
    }

    shaderManager->setInt(shader, ShaderVariables::DIRECTIONAL_LIGHTS_COUNT, count);
}

void LightRendererShaderSetup::setupPointValues(Shader *shader)
{
    char variable[100];

    PointLightComponent *light = nullptr;
    int count = this->lightManager->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        light = this->lightManager->pointLights[i];

        sprintf_s(variable, POINT_POSITION_FORMAT, i);
        shaderManager->setVec3(shader, variable, &light->getPosition()[0]);

        sprintf_s(variable, POINT_COLOR_FORMAT, i);
        shaderManager->setVec3(shader, variable, &light->getColor()[0]);

        sprintf_s(variable, POINT_RANGE_FORMAT, i);
        shaderManager->setFloat(shader, variable, light->getRange());

        sprintf_s(variable, POINT_INTENSITY_FORMAT, i);
        shaderManager->setFloat(shader, variable, light->getIntensity());
    }

    shaderManager->setInt(shader, ShaderVariables::POINT_LIGHTS_COUNT, count);
}

} // namespace
