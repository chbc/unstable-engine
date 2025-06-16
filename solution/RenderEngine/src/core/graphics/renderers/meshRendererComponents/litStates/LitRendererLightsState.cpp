#include "LitRendererLightsState.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "LitMaterialComponent.h"

namespace sre
{

void LitRendererLightsState::onSceneLoaded(ShaderManager *shaderManager, uint32_t program)
{
    shaderManager->setupUniformLocation(program, ShaderVariables::SHININESS);
}

void LitRendererLightsState::setupShaderValues(ShaderManager *shaderManager, MeshComponent *mesh, uint32_t program)
{
    LitMaterialComponent *litComponent = mesh->getMaterial()->getComponent<LitMaterialComponent>();
    shaderManager->setFloat(program, ShaderVariables::SHININESS, litComponent->getShininess());
}

void LitRendererLightsState::preDraw(AGraphicsWrapper *graphicsWrapper)
{
    graphicsWrapper->enableVertexNormals();
}

void LitRendererLightsState::postDraw(AGraphicsWrapper *graphicsWrapper)
{
    graphicsWrapper->disableVertexNormals();
}

} // namespace
