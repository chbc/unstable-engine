#include "LightRendererShaderSetup.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "CameraComponent.h"
#include "PointLightComponent.h"
#include "TransformComponent.h"
#include "StringUtils.h"

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

void LightRendererShaderSetup::setupShaderValues(Shader *shader)
{
    if (this->lightManager->directionalLights.size() > 0)
        this->setupDirectionalValues(shader);

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointValues(shader);

    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    CameraComponent* camera = renderManager->getCurrentCamera();
    TransformComponent* cameraTransform = camera->getTransform();
    const glm::vec3& cameraPosition = cameraTransform->getInternalMatrixPosition();

	this->shaderManager->setVec3(shader, ShaderVariables::CAMERA_POSITION, &cameraPosition[0]);
	this->shaderManager->setVec3(shader, ShaderVariables::AMBIENT_LIGHT_COLOR, &this->lightManager->ambientLightColor[0]);
}

void LightRendererShaderSetup::setupDirectionalsVariablesLocations(Shader *shader)
{
    std::string variable;

    size_t size = this->lightManager->directionalLights.size();
    for (size_t i = 0; i < size; i++)
    {
        variable = StringUtils::format(DIRECTIONAL_DIRECTION_FORMAT, i);
		this->shaderManager->setupUniformLocation(shader, variable.c_str());

        variable = StringUtils::format(DIRECTIONAL_COLOR_FORMAT, i);
		this->shaderManager->setupUniformLocation(shader, variable.c_str());
    }
}

void LightRendererShaderSetup::setupPointsVariablesLocations(Shader *shader)
{
    std::string variable;

    size_t size = this->lightManager->pointLights.size();
    for (int i = 0; i < size; i++)
    {
        variable = StringUtils::format(POINT_POSITION_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable.c_str());

        variable = StringUtils::format(POINT_COLOR_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable.c_str());

        variable = StringUtils::format(POINT_RANGE_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable.c_str());

        variable = StringUtils::format(POINT_INTENSITY_FORMAT, i);
        this->shaderManager->setupUniformLocation(shader, variable.c_str());
    }
}

void LightRendererShaderSetup::setupDirectionalValues(Shader *shader)
{
    std::string variable;

    DirectionalLightComponent *light = nullptr;
    size_t size = this->lightManager->directionalLights.size();
    for (int i = 0; i < size; i++)
    {
        light = this->lightManager->directionalLights[i];
        TransformComponent* transform = light->getTransform();
        glm::vec3 direction = transform->getForward();
        glm::vec3 color = light->getColor();

        variable = StringUtils::format(DIRECTIONAL_DIRECTION_FORMAT, i);
        this->shaderManager->setVec3(shader, variable.c_str(), &direction[0]);

        variable = StringUtils::format(DIRECTIONAL_COLOR_FORMAT, i);
        this->shaderManager->setVec3(shader, variable.c_str(), &color[0]);
    }
}

void LightRendererShaderSetup::setupPointValues(Shader *shader)
{
    std::string variable;


    PointLightComponent *light = nullptr;
    size_t size = this->lightManager->pointLights.size();
    for (int i = 0; i < size; i++)
    {
        light = this->lightManager->pointLights[i];
        TransformComponent* transform = light->getTransform();
        const glm::vec3& position = transform->getInternalMatrixPosition();

        variable = StringUtils::format(POINT_POSITION_FORMAT, i);
        this->shaderManager->setVec3(shader, variable.c_str(), &position[0]);

        variable = StringUtils::format(POINT_COLOR_FORMAT, i);
        this->shaderManager->setVec3(shader, variable.c_str(), &light->getColor()[0]);

        variable = StringUtils::format(POINT_RANGE_FORMAT, i);
        this->shaderManager->setFloat(shader, variable.c_str(), light->getRange());

        variable = StringUtils::format(POINT_INTENSITY_FORMAT, i);
        this->shaderManager->setFloat(shader, variable.c_str(), light->getIntensity());
    }
}

} // namespace
