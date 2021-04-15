#include "AORendererComponent.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "EMaterialMap.h"
#include "AmbientOcclusionMaterialComponent.h"

namespace sre
{

AORendererComponent::AORendererComponent(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
    : DiffuseRendererComponent(shaderManager, graphicsWrapper)
{
}

void AORendererComponent::onSceneLoaded(Shader* shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::AO_TEXTURE);
}

void AORendererComponent::setupShaderValues(MeshComponent* mesh, Shader* shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::AO_TEXTURE, EMaterialMap::AMBIENT_OCCLUSION);
    this->textureId = mesh->getMaterial()->getComponent<AmbientOcclusionMaterialComponent>()->getTextureID();
}

void AORendererComponent::preDraw(Shader* shader)
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activateAOTexture(this->textureId);
}

void AORendererComponent::postDraw(Shader* shader)
{
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
