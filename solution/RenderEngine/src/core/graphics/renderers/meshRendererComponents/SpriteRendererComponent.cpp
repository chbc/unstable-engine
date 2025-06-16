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
	this->textureId = mesh->getMaterial()->getComponent<SpriteMaterialComponent>()->getTextureID();
}
	
} // namespace
