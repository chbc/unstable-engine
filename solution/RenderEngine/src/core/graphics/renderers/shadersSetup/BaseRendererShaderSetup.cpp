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
    this->shaderManager->setupUniformLocation(program, ShaderVariables::MODEL_MATRIX);
    this->shaderManager->setupUniformLocation(program, ShaderVariables::NORMAL_MATRIX);
}

} // namespace
