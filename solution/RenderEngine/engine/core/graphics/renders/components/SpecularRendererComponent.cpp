#include "SpecularRendererComponent.h"

#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

SpecularRendererComponent::SpecularRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void SpecularRendererComponent::onSceneLoaded(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::SPECULAR_TEXTURE);
}

void SpecularRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::SPECULAR_TEXTURE, 2);
    this->textureId = mesh->getMaterial()->getComponent<SpecularMaterialComponent>()->getTextureID();
}

void SpecularRendererComponent::preDraw()
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activeSpecularTexture(this->textureId);
}

void SpecularRendererComponent::postDraw()
{
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
