#include "DiffuseRendererComponent.h"

#include "MeshComponent.h"
#include "Material.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "ETextureMap.h"
#include "DiffuseMaterialComponent.h"

namespace sre
{

DiffuseRendererComponent::DiffuseRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
    : ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void DiffuseRendererComponent::onSceneLoaded(uint32_t program)
{
    this->shaderManager->setupUniformLocation(program, ShaderVariables::DIFFUSE_TEXTURE);
    this->shaderManager->setupUniformLocation(program, ShaderVariables::UV_OFFSET);
    this->shaderManager->setupUniformLocation(program, ShaderVariables::UV_TILING);
    this->shaderManager->setupAttributeLocation(program, ShaderVariables::IN_TEXTURE_COORDS);
}

void DiffuseRendererComponent::setupShaderValues(MeshComponent *mesh, uint32_t program)
{
    this->shaderManager->setInt(program, ShaderVariables::DIFFUSE_TEXTURE, ETextureMap::DIFFUSE);

    Material* material = mesh->getMaterial();
    glm::vec2 uvOffset = material->getUVOffset();
    float uvOffsetData[2] = { uvOffset.x, uvOffset.y };
    glm::vec2 uvTiling = material->getUVTiling();
    float uvTilingData[2] = { uvTiling.x, uvTiling.y };

    this->shaderManager->setVec2(program, ShaderVariables::UV_OFFSET, uvOffsetData);
    this->shaderManager->setVec2(program, ShaderVariables::UV_TILING, uvTilingData);
    this->textureId = material->getComponent<DiffuseMaterialComponent>()->getTextureID();
}

void DiffuseRendererComponent::preDraw(uint32_t program)
{
    this->graphicsWrapper->enableTexCoords();
    this->graphicsWrapper->activateDiffuseTexture(this->textureId);
}

void DiffuseRendererComponent::postDraw(uint32_t program)
{
    // ### TALVEZ NÃO SEJA DESNECESSÁRIO CHAMAR MAIS DE UMA VEZ
    this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_POSITION);

    this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_TEXTURE_COORDS);
}

} // namespace
