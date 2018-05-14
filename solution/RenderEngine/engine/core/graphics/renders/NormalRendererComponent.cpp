#include "NormalRendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

NormalRendererComponent::NormalRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void NormalRendererComponent::onLoadShader(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::NORMAL_TEXTURE);
}

void NormalRendererComponent::setupShaderVariables(MeshComponent *mesh, Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::NORMAL_TEXTURE, 1);
    this->textureId = mesh->getMaterial()->getComponent<NormalMaterialComponent>()->getTextureID();
}

void NormalRendererComponent::preDraw()
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->enableVertexTangents();
    this->graphicsWrapper->enableVertexBitangents();
    this->graphicsWrapper->activeNormalTexture(this->textureId);
}

void NormalRendererComponent::postDraw()
{
    this->graphicsWrapper->disableVertexTangents();
    this->graphicsWrapper->disableVertexBitangents();
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
