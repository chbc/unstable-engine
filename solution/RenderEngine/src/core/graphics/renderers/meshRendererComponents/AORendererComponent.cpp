#include "AORendererComponent.h"

#include "MeshComponent.h"
#include "Material.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "ETextureMap.h"
#include "AmbientOcclusionMaterialComponent.h"

namespace sre
{

AORendererComponent::AORendererComponent(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
    : DiffuseRendererComponent(shaderManager, graphicsWrapper)
{
}

void AORendererComponent::onSceneLoaded(uint32_t program)
{
    this->shaderManager->setupUniformLocation(program, ShaderVariables::AO_TEXTURE);
}

void AORendererComponent::setupShaderValues(MeshComponent* mesh, uint32_t program)
{
    this->shaderManager->setInt(program, ShaderVariables::AO_TEXTURE, ETextureMap::AMBIENT_OCCLUSION);
    Material* material = static_cast<Material*>(mesh->getMaterial());
    this->textureId = material->getComponent<AmbientOcclusionMaterialComponent>()->getTextureID();
}

void AORendererComponent::preDraw(uint32_t program)
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activateAOTexture(this->textureId);
}

void AORendererComponent::postDraw(uint32_t program)
{
    this->graphicsWrapper->disableTexCoords();
}

} // namespace
