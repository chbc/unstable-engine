#include "SpecularRendererComponent.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "EMaterialMap.h"
#include "SpecularMaterialComponent.h"

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
    this->shaderManager->setInt(shader, ShaderVariables::SPECULAR_TEXTURE, ETextureMap::SPECULAR);
    this->textureId = mesh->getMaterial()->getComponent<SpecularMaterialComponent>()->getTextureID();
}

void SpecularRendererComponent::preDraw(Shader* shader)
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activateSpecularTexture(this->textureId);
}

void SpecularRendererComponent::postDraw(Shader* shader)
{
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
