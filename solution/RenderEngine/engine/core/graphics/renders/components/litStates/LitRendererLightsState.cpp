#include "LitRendererLightsState.h"

#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

void LitRendererLightsState::onSceneLoaded(ShaderManager *shaderManager, Shader *shader)
{
    shaderManager->setupUniformLocation(shader, ShaderVariables::SHININESS);
}

void LitRendererLightsState::setupShaderValues(ShaderManager *shaderManager, MeshComponent *mesh, Shader *shader)
{
    LitMaterialComponent *litComponent = mesh->getMaterial()->getComponent<LitMaterialComponent>();
    shaderManager->setFloat(shader, ShaderVariables::SHININESS, litComponent->getShininess());
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
