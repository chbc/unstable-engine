#include "NormalRendererComponent.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "EMaterialMap.h"
#include "NormalMaterialComponent.h"

namespace sre
{

NormalRendererComponent::NormalRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void NormalRendererComponent::onSceneLoaded(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::NORMAL_TEXTURE);
}

void NormalRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::NORMAL_TEXTURE, EMaterialMap::NORMAL);
    this->textureId = mesh->getMaterial()->getComponent<NormalMaterialComponent>()->getTextureID();
}

void NormalRendererComponent::preDraw(Shader* shader)
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->enableVertexTangents();
    this->graphicsWrapper->enableVertexBitangents();
    this->graphicsWrapper->activateNormalTexture(this->textureId);
}

void NormalRendererComponent::postDraw(Shader* shader)
{
    this->graphicsWrapper->disableVertexTangents();
    this->graphicsWrapper->disableVertexBitangents();
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
