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
	this->shaderManager->setupUniformLocation(program, ShaderVariables::CAMERA_POSITION);
}

void LightRendererShaderSetup::setupShaderValues(uint32_t program)
{
    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    CameraComponent* camera = renderManager->getCurrentCamera();
    TransformComponent* cameraTransform = camera->getTransform();
    const glm::vec3& cameraPosition = cameraTransform->getInternalMatrixPosition();

	this->shaderManager->setVec3(program, ShaderVariables::CAMERA_POSITION, &cameraPosition[0]);
}

} // namespace
