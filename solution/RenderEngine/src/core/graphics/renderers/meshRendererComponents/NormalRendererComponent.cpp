#include "NormalRendererComponent.h"

#include "MeshComponent.h"
#include "Material.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "ETextureMap.h"
#include "NormalMaterialComponent.h"

namespace sre
{

NormalRendererComponent::NormalRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void NormalRendererComponent::onSceneLoaded(uint32_t program)
{
    this->shaderManager->setupUniformLocation(program, ShaderVariables::NORMAL_TEXTURE);
}

void NormalRendererComponent::setupShaderValues(MeshComponent *mesh, uint32_t program)
{
    this->shaderManager->setInt(program, ShaderVariables::NORMAL_TEXTURE, ETextureMap::NORMAL);
    this->textureId = mesh->getMaterial()->getComponent<NormalMaterialComponent>()->getTextureID();
}

void NormalRendererComponent::preDraw(uint32_t program)
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->enableVertexTangents();
    this->graphicsWrapper->enableVertexBitangents();
    this->graphicsWrapper->activateNormalTexture(this->textureId);
}

void NormalRendererComponent::postDraw(uint32_t program)
{
    this->graphicsWrapper->disableVertexTangents();
    this->graphicsWrapper->disableVertexBitangents();
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
