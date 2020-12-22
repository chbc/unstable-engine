#include "DiffuseRendererComponent.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "EMaterialMap.h"

namespace sre
{

DiffuseRendererComponent::DiffuseRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void DiffuseRendererComponent::onSceneLoaded(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::DIFFUSE_TEXTURE);
}

void DiffuseRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::DIFFUSE_TEXTURE, EMaterialMap::DIFFUSE);
    this->textureId = mesh->getMaterial()->getComponent<DiffuseMaterialComponent>()->getTextureID();
}

void DiffuseRendererComponent::preDraw()
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activateDiffuseTexture(this->textureId);
}

// ### TALVEZ NÃO SEJA DESNECESSÁRIO CHAMAR MAIS DE UMA VEZ
void DiffuseRendererComponent::postDraw()
{
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
