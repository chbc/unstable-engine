#include "DiffuseRendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

DiffuseRendererComponent::DiffuseRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void DiffuseRendererComponent::onLoadShader(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::DIFFUSE_TEXTURE);
}

void DiffuseRendererComponent::setupShaderVariables(MeshComponent *mesh, Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::DIFFUSE_TEXTURE, 0);
    this->textureId = mesh->getMaterial()->getComponent<DiffuseMaterialComponent>()->getTextureID();
}

void DiffuseRendererComponent::preDraw()
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activeDiffuseTexture(this->textureId);
}

void DiffuseRendererComponent::postDraw()
{
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
