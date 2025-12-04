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
	this->shaderManager->setupAttributeLocation(program, ShaderVariables::IN_POSITION); // XXX APAGAR?
	this->shaderManager->setupAttributeLocation(program, ShaderVariables::IN_TEXTURE_COORDS); // XXX APAGAR?
	
	this->shaderManager->setupUniformLocation(program, ShaderVariables::UV_OFFSET);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::UV_TILING);

	this->shaderManager->setupUniformLocation(program, ShaderVariables::ALBEDO_TEXTURE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::NORMAL_TEXTURE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::METALLIC_TEXTURE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::ROUGHNESS_TEXTURE);
	this->shaderManager->setupUniformLocation(program, ShaderVariables::AO_TEXTURE);

	this->shaderManager->setupUniformLocation(program, ShaderVariables::NORMAL_FLIP_GREEN_CHANNEL);
}

void PBRRendererComponent::setupShaderValues(MeshComponent* mesh, uint32_t program)
{
	Material* material = static_cast<Material*>(mesh->getMaterial());
	glm::vec2 uvOffset = material->getUVOffset();
	float uvOffsetData[2] = { uvOffset.x, uvOffset.y };
	glm::vec2 uvTiling = material->getUVTiling();
	float uvTilingData[2] = { uvTiling.x, uvTiling.y };

	PBRMaterialComponent* pbrMaterial = material->getComponent<PBRMaterialComponent>();
	float normalFlipGreenChannel = pbrMaterial->getNormalFlipGreenChannelValue();

	this->shaderManager->setVec2(program, ShaderVariables::UV_OFFSET, uvOffsetData);
	this->shaderManager->setVec2(program, ShaderVariables::UV_TILING, uvTilingData);

	this->shaderManager->setInt(program, ShaderVariables::ALBEDO_TEXTURE, ETextureMap::DIFFUSE);
	this->shaderManager->setInt(program, ShaderVariables::NORMAL_TEXTURE, ETextureMap::NORMAL);
	this->shaderManager->setInt(program, ShaderVariables::METALLIC_TEXTURE, ETextureMap::METALLIC);
	this->shaderManager->setInt(program, ShaderVariables::ROUGHNESS_TEXTURE, ETextureMap::ROUGHNESS);
	this->shaderManager->setInt(program, ShaderVariables::AO_TEXTURE, ETextureMap::AMBIENT_OCCLUSION);
	this->shaderManager->setFloat(program, ShaderVariables::NORMAL_FLIP_GREEN_CHANNEL, normalFlipGreenChannel);

	this->albedoTextureId = pbrMaterial->getAlbedoTextureID();
	this->normalTextureId = pbrMaterial->getNormalTextureID();
	this->metallicTextureId = pbrMaterial->getMetallicTextureID();
	this->roughnessTextureId = pbrMaterial->getRoughnessTextureID();
	this->aoTextureId = pbrMaterial->getAOTextureID();
}

void PBRRendererComponent::preDraw(uint32_t program)
{
	this->graphicsWrapper->enableVertexPositions();
	this->graphicsWrapper->enableTexCoords();

	this->graphicsWrapper->activateTexture(this->albedoTextureId, ETextureMap::DIFFUSE);
	this->graphicsWrapper->activateTexture(this->normalTextureId, ETextureMap::NORMAL);
	this->graphicsWrapper->activateTexture(this->metallicTextureId, ETextureMap::METALLIC);
	this->graphicsWrapper->activateTexture(this->roughnessTextureId, ETextureMap::ROUGHNESS);
	this->graphicsWrapper->activateTexture(this->aoTextureId, ETextureMap::AMBIENT_OCCLUSION);
}

void PBRRendererComponent::postDraw(uint32_t program)
{
	this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_POSITION);
	this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_TEXTURE_COORDS);
}

} // namespace
