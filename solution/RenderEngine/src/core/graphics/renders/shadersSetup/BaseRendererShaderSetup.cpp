#include "BaseRendererShaderSetup.h"

#include "ShaderManager.h"
#include "MatrixManager.h"
#include "SingletonsManager.h"

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
    MatrixManager *matrixManager = SingletonsManager::getInstance()->get<MatrixManager>();

    glm::mat4 viewMatrix = matrixManager->getViewMatrix();
    glm::mat4 projectionMatrix = matrixManager->getProjectionMatrix();

    this->shaderManager->setMat4(shader, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
    this->shaderManager->setMat4(shader, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);
}

} // namespace
