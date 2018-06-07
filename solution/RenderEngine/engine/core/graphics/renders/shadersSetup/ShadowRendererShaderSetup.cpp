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
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::LIGHT_SPACE_MATRIX);
}

void ShadowRendererShaderSetup::setupShaderValues(Shader *shader)
{
    this->shaderManager->setMat4(shader, ShaderVariables::LIGHT_SPACE_MATRIX, &lightManager->lightSpaceMatrix[0][0]);
    this->shaderManager->setInt(shader, ShaderVariables::SHADOW_MAP, 4);

    this->graphicsWrapper->activateShadowMapTexture(this->lightManager->depthMap);
}

} // namespace
