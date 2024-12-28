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

void DiffuseRendererComponent::onSceneLoaded(Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::DIFFUSE_TEXTURE);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::UV_OFFSET);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::UV_TILING);
    this->shaderManager->setupAttributeLocation(shader, ShaderVariables::IN_TEXTURE_COORDS);
}

void DiffuseRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    this->shaderManager->setInt(shader, ShaderVariables::DIFFUSE_TEXTURE, ETextureMap::DIFFUSE);

    Material* material = mesh->getMaterial();
    glm::vec2 uvOffset = material->getUVOffset();
    float uvOffsetData[2] = { uvOffset.x, uvOffset.y };
    glm::vec2 uvTiling = material->getUVTiling();
    float uvTilingData[2] = { uvTiling.x, uvTiling.y };

    this->shaderManager->setVec2(shader, ShaderVariables::UV_OFFSET, uvOffsetData);
    this->shaderManager->setVec2(shader, ShaderVariables::UV_TILING, uvTilingData);
    this->textureId = material->getComponent<DiffuseMaterialComponent>()->getTextureID();
}

void DiffuseRendererComponent::preDraw(Shader* shader)
{
    this->shaderManager->setVertexAttributePointer(shader, ShaderVariables::IN_TEXTURE_COORDS, 2, sizeof(VertexData), ABaseVertexData::getUVOffset());
    this->graphicsWrapper->activateDiffuseTexture(this->textureId);
}

// ### TALVEZ N�O SEJA DESNECESS�RIO CHAMAR MAIS DE UMA VEZ
void DiffuseRendererComponent::postDraw(Shader* shader)
{
    this->shaderManager->disableVertexAttribute(shader, ShaderVariables::IN_POSITION);
}

} // namespace
