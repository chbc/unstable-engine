#include "AORendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

AORendererComponent::AORendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : DiffuseRendererComponent(shaderManager, graphicsWrapper)
{
}

void AORendererComponent::onLoadShader(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::AO_TEXTURE);
}

void AORendererComponent::setupShaderVariables(MeshComponent *mesh, Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::AO_TEXTURE, 3);
    this->textureId = mesh->getMaterial()->getComponent<AmbientOcclusionMaterialComponent>()->getTextureID();
}

void AORendererComponent::preDraw()
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activeAOTexture(this->textureId);
}

void AORendererComponent::postDraw()
{
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
