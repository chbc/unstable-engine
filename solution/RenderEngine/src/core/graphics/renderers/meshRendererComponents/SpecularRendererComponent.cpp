#include "SpecularRendererComponent.h"

#include "MeshComponent.h"
#include "Material.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "ETextureMap.h"
#include "SpecularMaterialComponent.h"

namespace sre
{

SpecularRendererComponent::SpecularRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void SpecularRendererComponent::onSceneLoaded(uint32_t program)
{
    this->shaderManager->setupUniformLocation(program, ShaderVariables::SPECULAR_TEXTURE);
}

void SpecularRendererComponent::setupShaderValues(MeshComponent *mesh, uint32_t program)
{
    this->shaderManager->setInt(program, ShaderVariables::SPECULAR_TEXTURE, ETextureMap::SPECULAR);
    this->textureId = mesh->getMaterial()->getComponent<SpecularMaterialComponent>()->getTextureID();
}

void SpecularRendererComponent::preDraw(uint32_t program)
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activateSpecularTexture(this->textureId);
}

void SpecularRendererComponent::postDraw(uint32_t program)
{
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
