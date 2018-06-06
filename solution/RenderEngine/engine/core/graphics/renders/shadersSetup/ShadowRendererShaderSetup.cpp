#include "ShadowRendererShaderSetup.h"
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/graphics/LightManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <glm/gtc/matrix_transform.hpp>

namespace sre
{

ShadowRendererShaderSetup::ShadowRendererShaderSetup(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : BaseRendererShaderSetup(shaderManager, graphicsWrapper)
{ 
    this->lightManager = SingletonsManager::getInstance()->get<LightManager>();
}

void ShadowRendererShaderSetup::onSceneLoaded(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::SHADOW_MAP);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::SOURCE_SPACE_MATRIX);
}

void ShadowRendererShaderSetup::setupShaderValues(Shader *shader)
{
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
    glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 4.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    this->shaderManager->setMat4(shader, ShaderVariables::SOURCE_SPACE_MATRIX, &lightSpaceMatrix[0][0]);

    this->graphicsWrapper->activateShadowMapTexture(this->lightManager->depthMap);

    this->shaderManager->setInt(shader, ShaderVariables::SHADOW_MAP, 4);
}

} // namespace
