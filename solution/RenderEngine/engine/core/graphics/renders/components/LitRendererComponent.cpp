#include "LitRendererComponent.h"
#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

    LitRendererComponent::LitRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void LitRendererComponent::onSceneLoaded(class Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::SHININESS);
}

void LitRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    LitMaterialComponent *litComponent = mesh->getMaterial()->getComponent<LitMaterialComponent>();
    this->shaderManager->setFloat(shader, ShaderVariables::SHININESS, litComponent->getShininess());
}

void LitRendererComponent::preDraw()
{
    this->graphicsWrapper->enableVertexNormals();
}

void LitRendererComponent::postDraw()
{
    this->graphicsWrapper->disableVertexNormals();
}

} // namespace
