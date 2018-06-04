#include "LightRendererComponent.h"
#include <engine/core/graphics/LightManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/entities/components/lights/PointLightComponent.h>

#include <glm/gtc/matrix_transform.hpp> // ### SOMBRA

namespace sre
{

LightRendererComponent::LightRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : ColorRendererComponent(shaderManager, graphicsWrapper)
{
    this->lightManager = SingletonsManager::getInstance()->get<LightManager>();
}

void LightRendererComponent::onLoadShader(Shader *shader)
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

    // ### SOMBRA
    shaderManager->setupUniformLocation(shader, ShaderVariables::AMBIENT_LIGHT_COLOR);
    shaderManager->setupUniformLocation(shader, ShaderVariables::SHADOW_MAP);
    shaderManager->setupUniformLocation(shader, ShaderVariables::SOURCE_SPACE_MATRIX);
}

void LightRendererComponent::setupShaderVariables(MeshComponent *mesh, Shader *shader)
{
    if (this->lightManager->directionalLights.size() > 0)
        this->setupDirectionalValues(shader);

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointValues(shader);

    shaderManager->setVec3(shader, ShaderVariables::AMBIENT_LIGHT_COLOR, &this->lightManager->ambientLightColor[0]);

    // ### SOMBRA
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
    glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 4.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    shaderManager->setMat4(shader, ShaderVariables::SOURCE_SPACE_MATRIX, &lightSpaceMatrix[0][0]);

    this->graphicsWrapper->activateShadowMapTexture(this->lightManager->depthMap); // ### PRE_RENDER

    shaderManager->setInt(shader, ShaderVariables::SHADOW_MAP, 4);
}

void LightRendererComponent::setupDirectionalsVariablesLocations(Shader *shader)
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

void LightRendererComponent::setupPointsVariablesLocations(Shader *shader)
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

void LightRendererComponent::setupDirectionalValues(Shader *shader)
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

void LightRendererComponent::setupPointValues(Shader *shader)
{
    char variable[100];

    PointLightComponent *light = nullptr;
    int count = this->lightManager->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        // ### COLOCAR DIRETO
        light = this->lightManager->pointLights[i];
        glm::vec3 position = light->getPosition();
        glm::vec3 color = light->getColor();
        float range = light->getRange();
        float intensity = light->getIntensity();

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
