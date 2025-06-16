#include "BaseRendererShaderSetup.h"

#include "ShaderManager.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

namespace sre
{

BaseRendererShaderSetup::BaseRendererShaderSetup(ShaderManager *arg_shaderManager, AGraphicsWrapper *arg_graphicsWrapper)
    : shaderManager(arg_shaderManager), graphicsWrapper(arg_graphicsWrapper)
{
}

void BaseRendererShaderSetup::onSceneLoaded(uint32_t program)
{
    this->shaderManager->setupUniformLocation(program, ShaderVariables::VIEW_MATRIX);
    this->shaderManager->setupUniformLocation(program, ShaderVariables::PROJECTION_MATRIX);
    this->shaderManager->setupUniformLocation(program, ShaderVariables::MODEL_MATRIX);
}

void BaseRendererShaderSetup::setupShaderValues(uint32_t program)
{
    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    CameraComponent* camera = renderManager->getCurrentCamera();

    const glm::mat4& viewMatrix = camera->getViewMatrix();
    const glm::mat4& projectionMatrix = camera->getProjectionMatrix();

    this->shaderManager->setMat4(program, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
    this->shaderManager->setMat4(program, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);
}

} // namespace
