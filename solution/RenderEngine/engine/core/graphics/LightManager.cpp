#include "LightManager.h"

#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/entities/Entity.h>
#include "ShaderManager.h"

namespace sre
{

LightManager::LightManager()
{
    this->ambientLightColor = glm::vec3(0.1f, 0.1f, 0.1f);
}

void LightManager::setAmbientLightColor(const glm::vec3 &ambientLightColor)
{
    this->ambientLightColor = ambientLightColor;
}

DirectionalLightComponent *LightManager::addDirectionalLight(Entity *entity)
{
    DirectionalLightComponent *newLight = entity->addComponent<DirectionalLightComponent>();
    this->directionalLights.push_back(newLight);

    return newLight;
}

PointLightComponent *LightManager::addPointLight(Entity *entity)
{
    PointLightComponent *newLight = entity->addComponent<PointLightComponent>();
    this->pointLights.push_back(newLight);

    return newLight;
}

void LightManager::onSceneLoaded()
{
    ShaderManager *shaderManager = SingletonsManager::getInstance()->resolve<ShaderManager>();
    this->setupVariablesLocations(shaderManager);
}

void LightManager::setupVariablesLocations(ShaderManager *shaderManager)
{
    bool hasAnyLight = false;

    if (this->directionalLights.size() > 0)
    {
        shaderManager->setupUniformLocation(ShaderVariables::DIRECTIONAL_LIGHTS_COUNT);
        this->setupDirectionalsVariablesLocations(shaderManager);
        hasAnyLight = true;
    }

    if (this->pointLights.size() > 0)
    {
        shaderManager->setupUniformLocation(ShaderVariables::POINT_LIGHTS_COUNT);
        this->setupPointsVariablesLocations(shaderManager);
        hasAnyLight = true;
    }

    if (hasAnyLight)
        shaderManager->setupUniformLocation(ShaderVariables::AMBIENT_LIGHT_COLOR);
}

void LightManager::setupDirectionalsVariablesLocations(ShaderManager *shaderManager)
{
    char variable[128];

    int count = this->directionalLights.size();
    for (int i = 0; i < count; i++)
    {
        sprintf_s(variable, DIRECTIONAL_DIRECTION_FORMAT, i);
        shaderManager->setupUniformLocation(variable);

        sprintf_s(variable, DIRECTIONAL_COLOR_FORMAT, i);
        shaderManager->setupUniformLocation(variable);
    }
}

void LightManager::setupPointsVariablesLocations(ShaderManager *shaderManager)
{
    char variable[128];

    int count = this->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        sprintf_s(variable, POINT_POSITION_FORMAT, i);
        shaderManager->setupUniformLocation(variable);

        sprintf_s(variable, POINT_COLOR_FORMAT, i);
        shaderManager->setupUniformLocation(variable);

        sprintf_s(variable, POINT_RANGE_FORMAT, i);
        shaderManager->setupUniformLocation(variable);

        sprintf_s(variable, POINT_INTENSITY_FORMAT, i);
        shaderManager->setupUniformLocation(variable);
    }
}

// Renderer::render() ->
void LightManager::setupValues(ShaderManager *shaderManager, Shader *shader)
{
    bool hasAnyLight = false;

    if (this->directionalLights.size() > 0)
    {
        this->setupDirectionalValues(shaderManager, shader);
        hasAnyLight = true;
    }

    if (this->pointLights.size() > 0)
    {
        this->setupPointValues(shaderManager, shader);
        hasAnyLight = true;
    }

    if (hasAnyLight)
        shaderManager->setVec3(shader, ShaderVariables::AMBIENT_LIGHT_COLOR, &this->ambientLightColor[0]);
}

void LightManager::setupDirectionalValues(ShaderManager *shaderManager, Shader *shader)
{
    char variable[100];

    DirectionalLightComponent *light = nullptr;
    int count = this->directionalLights.size();
    for (int i = 0; i < count; i++)
    {
        light = this->directionalLights[i];
        glm::vec3 direction = light->getDirection();
        glm::vec3 color = light->getColor();

        sprintf_s(variable, DIRECTIONAL_DIRECTION_FORMAT, i);
        shaderManager->setVec3(shader, variable, &direction[0]);

        sprintf_s(variable, DIRECTIONAL_COLOR_FORMAT, i);
        shaderManager->setVec3(shader, variable, &color[0]);
    }

    shaderManager->setInt(shader, ShaderVariables::DIRECTIONAL_LIGHTS_COUNT, count);
}

void LightManager::setupPointValues(ShaderManager *shaderManager, Shader *shader)
{
    char variable[100];

    PointLightComponent *light = nullptr;
    int count = this->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        light = this->pointLights[i];
        glm::vec3 position  = light->getTransform()->getPosition();
        glm::vec3 color     = light->getColor();
        float range         = light->getRange();
        float intensity     = light->getIntensity();

        sprintf_s(variable, POINT_POSITION_FORMAT, i);
        shaderManager->setVec3(shader, variable, &position[0]);

        sprintf_s(variable, POINT_COLOR_FORMAT, i);
        shaderManager->setVec3(shader, variable, &color[0]);

        sprintf_s(variable, POINT_RANGE_FORMAT, i);
        shaderManager->setFloat(shader, variable, range);

        sprintf_s(variable, POINT_INTENSITY_FORMAT, i);
        shaderManager->setFloat(shader, variable, intensity);
    }

    shaderManager->setInt(shader, ShaderVariables::POINT_LIGHTS_COUNT, count);
}

} // namespace
