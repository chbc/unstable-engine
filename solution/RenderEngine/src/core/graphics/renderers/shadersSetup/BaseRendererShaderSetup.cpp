#include "BaseRendererShaderSetup.h"

#include "ShaderManager.h"
#include "SingletonsManager.h"
#include "RenderManager.h"
#include "CameraComponent.h"

namespace sre
{

BaseRendererShaderSetup::BaseRendererShaderSetup(ShaderManager *arg_shaderManager, AGraphicsWrapper *arg_graphicsWrapper)
    : shaderManager(arg_shaderManager), graphicsWrapper(arg_graphicsWrapper)
{
}

void BaseRendererShaderSetup::onSceneLoaded(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::VIEW_MATRIX);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::PROJECTION_MATRIX);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::MODEL_MATRIX);
}

void BaseRendererShaderSetup::setupShaderValues(Shader *shader, const glm::vec3& cameraPosition)
{
    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    CameraComponent* cameraComponent = renderManager->getCurrentCamera();

    glm::mat4 viewMatrix = cameraComponent->getViewMatrix();
    glm::mat4 projectionMatrix = cameraComponent->getProjectionMatrix();

    this->shaderManager->setMat4(shader, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
    this->shaderManager->setMat4(shader, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);
}

} // namespace
