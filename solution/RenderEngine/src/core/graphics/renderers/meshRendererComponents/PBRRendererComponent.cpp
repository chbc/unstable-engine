#include "PBRRendererComponent.h"
#include "PBRMaterialComponent.h"
#include "MeshComponent.h"
#include "Material.h"
#include "ETextureMap.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"

namespace sre
{

PBRRendererComponent::PBRRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
	: ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void PBRRendererComponent::onSceneLoaded(uint32_t program)
{
	this->shaderManager->setupAttributeLocation(program, ShaderVariables::IN_POSITION);

	this->shaderManager->setupUniformLocation(program, ShaderVariables::ALBEDO_TEXTURE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::NORMAL_TEXTURE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::METALLIC_TEXTURE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::ROUGHNESS_TEXTURE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::AO_TEXTURE);

	this->shaderManager->setupUniformLocation(program, ShaderVariables::UV_OFFSET);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::UV_TILING);
	this->shaderManager->setupAttributeLocation(program, ShaderVariables::IN_TEXTURE_COORDS);
}

void PBRRendererComponent::setupShaderValues(MeshComponent* mesh, uint32_t program)
{
	Material* material = mesh->getMaterial();
	glm::vec2 uvOffset = material->getUVOffset();
	float uvOffsetData[2] = { uvOffset.x, uvOffset.y };
	glm::vec2 uvTiling = material->getUVTiling();
	float uvTilingData[2] = { uvTiling.x, uvTiling.y };

	this->shaderManager->setVec2(program, ShaderVariables::UV_OFFSET, uvOffsetData);
	this->shaderManager->setVec2(program, ShaderVariables::UV_TILING, uvTilingData);

	this->shaderManager->setInt(program, ShaderVariables::ALBEDO_TEXTURE, ETextureMap::DIFFUSE);
	this->shaderManager->setInt(program, ShaderVariables::NORMAL_TEXTURE, ETextureMap::NORMAL);
	this->shaderManager->setInt(program, ShaderVariables::METALLIC_TEXTURE, ETextureMap::METALLIC);
	this->shaderManager->setInt(program, ShaderVariables::ROUGHNESS_TEXTURE, ETextureMap::ROUGHNESS);
	this->shaderManager->setInt(program, ShaderVariables::AO_TEXTURE, ETextureMap::AMBIENT_OCCLUSION);
	this->albedoTextureId = material->getComponent<PBRMaterialComponent>()->getAlbedoTextureID();
	this->normalTextureId = material->getComponent<PBRMaterialComponent>()->getNormalTextureID();
	this->metallicTextureId = material->getComponent<PBRMaterialComponent>()->getMetallicTextureID();
	this->roughnessTextureId = material->getComponent<PBRMaterialComponent>()->getRoughnessTextureID();
	this->aoTextureId = material->getComponent<PBRMaterialComponent>()->getAOTextureID();
}

void PBRRendererComponent::preDraw(uint32_t program)
{
	this->graphicsWrapper->enableVertexPositions();
	this->graphicsWrapper->enableTexCoords();

	this->graphicsWrapper->activateDiffuseTexture(this->albedoTextureId);
	this->graphicsWrapper->activateNormalTexture(this->normalTextureId);
	this->graphicsWrapper->activateMetallicTexture(this->metallicTextureId);
	this->graphicsWrapper->activateRoughnessTexture(this->roughnessTextureId);
	this->graphicsWrapper->activateAOTexture(this->aoTextureId);
}

void PBRRendererComponent::postDraw(uint32_t program)
{
	this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_POSITION);
	this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_TEXTURE_COORDS);
}

} // namespace
