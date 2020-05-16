#include "LightRendererShaderSetup.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "SingletonsManager.h"
#include "PointLightComponent.h"

namespace sre
{

LightRendererShaderSetup::LightRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : BaseRendererShaderSetup(shaderManager, graphicsWrapper)
{
    this->lightManager = SingletonsManager::getInstance()->get<LightManager>();
}

void LightRendererShaderSetup::onSceneLoaded(Shader *shader)
{
    if (lightManager->directionalLights.size() > 0)
        this->setupDirectionalsVariablesLocations(shader);

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointsVariablesLocations(shader);

	this->shaderManager->setupUniformLocation(shader, ShaderVariables::CAMERA_POSITION);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::AMBIENT_LIGHT_COLOR);
}

void LightRendererShaderSetup::setupShaderValues(Shader *shader, const glm::vec3& cameraPosition)
{
    if (this->lightManager->directionalLights.size() > 0)
        this->setupDirectionalValues(shader);

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointValues(shader);

	this->shaderManager->setVec3(shader, ShaderVariables::CAMERA_POSITION, &cameraPosition[0]);
	this->shaderManager->setVec3(shader, ShaderVariables::AMBIENT_LIGHT_COLOR, &this->lightManager->ambientLightColor[0]);
}

void LightRendererShaderSetup::setupDirectionalsVariablesLocations(Shader *shader)
{
    char variable[128];

    int count = this->lightManager->directionalLights.size();
    for (int i = 0; i < count; i++)
    {
        std::sprintf(variable, DIRECTIONAL_DIRECTION_FORMAT, i);
		this->shaderManager->setupUniformLocation(shader, variable);

        std::sprintf(variable, DIRECTIONAL_COLOR_FORMAT, i);
		this->shaderManager->setupUniformLocation(shader, variable);
    }
}

void LightRendererShaderSetup::setupPointsVariablesLocations(Shader *shader)
{
    char variable[128];

    int count = this->lightManager->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        std::sprintf(variable, POINT_POSITION_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);

        std::sprintf(variable, POINT_COLOR_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);

        std::sprintf(variable, POINT_RANGE_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);

        std::sprintf(variable, POINT_INTENSITY_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable);
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

        std::sprintf(variable, DIRECTIONAL_DIRECTION_FORMAT, i);
        this->shaderManager->setVec3(shader, variable, &direction[0]);

        std::sprintf(variable, DIRECTIONAL_COLOR_FORMAT, i);
        this->shaderManager->setVec3(shader, variable, &color[0]);
    }
}

void LightRendererShaderSetup::setupPointValues(Shader *shader)
{
    char variable[100];

    PointLightComponent *light = nullptr;
    int count = this->lightManager->pointLights.size();
    for (int i = 0; i < count; i++)
    {
        light = this->lightManager->pointLights[i];

        std::sprintf(variable, POINT_POSITION_FORMAT, i);
        this->shaderManager->setVec3(shader, variable, &light->getPosition()[0]);

        std::sprintf(variable, POINT_COLOR_FORMAT, i);
        this->shaderManager->setVec3(shader, variable, &light->getColor()[0]);

        std::sprintf(variable, POINT_RANGE_FORMAT, i);
        this->shaderManager->setFloat(shader, variable, light->getRange());

        std::sprintf(variable, POINT_INTENSITY_FORMAT, i);
        this->shaderManager->setFloat(shader, variable, light->getIntensity());
    }
}

} // namespace
