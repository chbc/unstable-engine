#include "DiffuseRendererComponent.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "EMaterialMap.h"
#include "DiffuseMaterialComponent.h"

namespace sre
{

DiffuseRendererComponent::DiffuseRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void DiffuseRendererComponent::onSceneLoaded(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::DIFFUSE_TEXTURE);
    this->shaderManager->setupAttributeLocation(shader, ShaderVariables::IN_TEXTURE_COORDS);
}

void DiffuseRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::DIFFUSE_TEXTURE, EMaterialMap::DIFFUSE);
    this->textureId = mesh->getMaterial()->getComponent<DiffuseMaterialComponent>()->getTextureID();
}

void DiffuseRendererComponent::preDraw(Shader* shader)
{
    this->shaderManager->setVertexAttributePointer(shader, ShaderVariables::IN_TEXTURE_COORDS, 2, sizeof(VertexData), ABaseVertexData::getUVOffset());
    this->graphicsWrapper->activateDiffuseTexture(this->textureId);
}

// ### TALVEZ NÃO SEJA DESNECESSÁRIO CHAMAR MAIS DE UMA VEZ
void DiffuseRendererComponent::postDraw(Shader* shader)
{
    this->shaderManager->disableVertexAttribute(shader, ShaderVariables::IN_POSITION);
}

} // namespace
