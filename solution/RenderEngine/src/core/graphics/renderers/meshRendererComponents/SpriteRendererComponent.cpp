/*
#include "SpriteRendererComponent.h"
#include "MeshComponent.h"
#include "Material.h"
#include "ShaderManager.h"
#include "ETextureMap.h"
#include "SpriteMaterialComponent.h"

namespace sre
{

SpriteRendererComponent::SpriteRendererComponent(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
	: DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void SpriteRendererComponent::setupShaderValues(MeshComponent* mesh, uint32_t program)
{
	this->shaderManager->setInt(program, ShaderVariables::DIFFUSE_TEXTURE, ETextureMap::DIFFUSE);
	Material* material = static_cast<Material*>(mesh->getMaterial());
	this->textureId = material->getComponent<SpriteMaterialComponent>()->getTextureID();
}
	
} // namespace
*/
