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
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::FAR_PLANE);
}

void ShadowRendererShaderSetup::setupShaderValues(Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::SHADOW_MAP, 4);

    float farPlane = 25.0f;
    this->shaderManager->setFloat(shader, ShaderVariables::FAR_PLANE, farPlane);

    this->graphicsWrapper->activateShadowMapTexture(this->lightManager->depthCubemap);
}

} // namespace
