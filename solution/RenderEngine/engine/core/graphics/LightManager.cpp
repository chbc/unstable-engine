#include "LightManager.h"

#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/entities/Entity.h>
#include "ShaderManager.h"
#include <engine/core/multimedia/textures/TextureManager.h>
#include <experimental/vector>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

#include <glm/gtc/matrix_transform.hpp> // ###

// ### TENTAR LightingRendererComponent
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
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();

    ShaderManager *shaderManager = singletonsManager->resolve<ShaderManager>();
    this->setupVariablesLocations(shaderManager);
}

// Renderer::render() ->
void LightManager::onPreRender(ShaderManager *shaderManager, Shader *shader)
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
    {
        shaderManager->setVec3(shader, ShaderVariables::AMBIENT_LIGHT_COLOR, &this->ambientLightColor[0]);

        // ###
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
        glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 4.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        shaderManager->setMat4(shader, ShaderVariables::SOURCE_SPACE_MATRIX, &lightSpaceMatrix[0][0]);

        AGraphicsWrapper *graphics = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
        graphics->activateShadowMapTexture(this->depthMap);

        shaderManager->setInt(shader, ShaderVariables::SHADOW_MAP, 4);
    }
}

void LightManager::setupDepthRendering(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
{
    // ###
    // 1. first render to depth map
    /*
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
    glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 10.0f, 0.0f), // ### glm::vec3(0.0f) - this->directionalLights[0]->getDirection(),
        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    shaderManager->enableShader(this->depthShader);
    shaderManager->setMat4(this->depthShader, ShaderVariables::SOURCE_SPACE_MATRIX, &lightSpaceMatrix[0][0]);

    graphicsWrapper->bindFrameBuffer(this->depthMapFBO, 1024, 1024);
    */
}

void LightManager::setupVariablesLocations(ShaderManager *shaderManager)
{
    bool hasAnyLight = false;

    if (this->directionalLights.size() > 0)
    {
        shaderManager->setupLightUniformLocations(ShaderVariables::DIRECTIONAL_LIGHTS_COUNT);
        this->setupDirectionalsVariablesLocations(shaderManager);
        hasAnyLight = true;
    }

    if (this->pointLights.size() > 0)
    {
        shaderManager->setupLightUniformLocations(ShaderVariables::POINT_LIGHTS_COUNT);
        this->setupPointsVariablesLocations(shaderManager);
        hasAnyLight = true;
    }

    if (hasAnyLight)
    {
        shaderManager->setupLightUniformLocations(ShaderVariables::AMBIENT_LIGHT_COLOR);
        shaderManager->setupLightUniformLocations(ShaderVariables::SHADOW_MAP);
        shaderManager->setupLightUniformLocations(ShaderVariables::SOURCE_SPACE_MATRIX);
    }
}

void LightManager::setupDirectionalsVariablesLocations(ShaderManager *shaderManager)
{
    char variable[128];

    int count = this->directionalLights.size();
    for (int i = 0; i < count; i++)
    {
        sprintf_s(variable, DIRECTIONAL_DIRECTION_FORMAT, i);
        shaderManager->setupLightUniformLocations(variable);

        sprintf_s(variable, DIRECTIONAL_COLOR_FORMAT, i);
        shaderManager->setupLightUniformLocations(variable);
    }
}

void LightManager::setupPointsVariablesLocations(ShaderManager *shaderManager)
{
    char variable[128];

    int count = this->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        sprintf_s(variable, POINT_POSITION_FORMAT, i);
        shaderManager->setupLightUniformLocations(variable);

        sprintf_s(variable, POINT_COLOR_FORMAT, i);
        shaderManager->setupLightUniformLocations(variable);

        sprintf_s(variable, POINT_RANGE_FORMAT, i);
        shaderManager->setupLightUniformLocations(variable);

        sprintf_s(variable, POINT_INTENSITY_FORMAT, i);
        shaderManager->setupLightUniformLocations(variable);
    }
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

void LightManager::removeDestroyedEntities()
{
    std::experimental::erase_if
    (
        this->directionalLights, 
        [](DirectionalLightComponent *item) { return !item->getEntity()->isAlive(); }
    );

    std::experimental::erase_if
    (
        this->pointLights,
        [](PointLightComponent *item) { return !item->getEntity()->isAlive(); }
    );
}

} // namespace
