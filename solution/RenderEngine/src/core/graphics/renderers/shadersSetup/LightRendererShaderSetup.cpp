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

void LightRendererShaderSetup::onSceneLoaded(uint32_t program)
{
    if (lightManager->directionalLights.size() > 0)
        this->setupDirectionalsVariablesLocations(program);

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointsVariablesLocations(program);

	this->shaderManager->setupUniformLocation(program, ShaderVariables::CAMERA_POSITION);
    this->shaderManager->setupUniformLocation(program, ShaderVariables::AMBIENT_LIGHT_COLOR);
}

void LightRendererShaderSetup::setupShaderValues(uint32_t program)
{
    if (this->lightManager->directionalLights.size() > 0)
        this->setupDirectionalValues(program);

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointValues(program);

    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    CameraComponent* camera = renderManager->getCurrentCamera();
    TransformComponent* cameraTransform = camera->getTransform();
    const glm::vec3& cameraPosition = cameraTransform->getInternalMatrixPosition();

	this->shaderManager->setVec3(program, ShaderVariables::CAMERA_POSITION, &cameraPosition[0]);
	this->shaderManager->setVec3(program, ShaderVariables::AMBIENT_LIGHT_COLOR, &this->lightManager->ambientLightColor[0]);
}

void LightRendererShaderSetup::setupDirectionalsVariablesLocations(uint32_t program)
{
    std::string variable;

    size_t size = this->lightManager->directionalLights.size();
    for (size_t i = 0; i < size; i++)
    {
        variable = StringUtils::format(DIRECTIONAL_DIRECTION_FORMAT, i);
		this->shaderManager->setupUniformLocation(program, variable.c_str());

        variable = StringUtils::format(DIRECTIONAL_COLOR_FORMAT, i);
		this->shaderManager->setupUniformLocation(program, variable.c_str());
    }
}

void LightRendererShaderSetup::setupPointsVariablesLocations(uint32_t program)
{
    std::string variable;

    size_t size = this->lightManager->pointLights.size();
    for (int i = 0; i < size; i++)
    {
        variable = StringUtils::format(POINT_POSITION_FORMAT, i);
        this->shaderManager->setupUniformLocation(program, variable.c_str());

        variable = StringUtils::format(POINT_COLOR_FORMAT, i);
        this->shaderManager->setupUniformLocation(program, variable.c_str());

        variable = StringUtils::format(POINT_RANGE_FORMAT, i);
        this->shaderManager->setupUniformLocation(program, variable.c_str());

        variable = StringUtils::format(POINT_INTENSITY_FORMAT, i);
        this->shaderManager->setupUniformLocation(program, variable.c_str());
    }
}

void LightRendererShaderSetup::setupDirectionalValues(uint32_t program)
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
        this->shaderManager->setVec3(program, variable.c_str(), &direction[0]);

        variable = StringUtils::format(DIRECTIONAL_COLOR_FORMAT, i);
        this->shaderManager->setVec3(program, variable.c_str(), &color[0]);
    }
}

void LightRendererShaderSetup::setupPointValues(uint32_t program)
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
        this->shaderManager->setVec3(program, variable.c_str(), &position[0]);

        variable = StringUtils::format(POINT_COLOR_FORMAT, i);
        this->shaderManager->setVec3(program, variable.c_str(), &light->getColor()[0]);

        variable = StringUtils::format(POINT_RANGE_FORMAT, i);
        this->shaderManager->setFloat(program, variable.c_str(), light->getRange());

        variable = StringUtils::format(POINT_INTENSITY_FORMAT, i);
        this->shaderManager->setFloat(program, variable.c_str(), light->getIntensity());
    }
}

} // namespace
