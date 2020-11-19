#include "SpriteRendererComponent.h"
#include "MeshComponent.h"
#include "ShaderManager.h"
#include "EMaterialMap.h"

namespace sre
{

SpriteRendererComponent::SpriteRendererComponent(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
	: DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void SpriteRendererComponent::setupShaderValues(MeshComponent* mesh, Shader* shader)
{
	this->shaderManager->setInt(shader, ShaderVariables::DIFFUSE_TEXTURE, EMaterialMap::DIFFUSE);
	this->textureId = mesh->getMaterial()->getComponent<SpriteMaterialComponent>()->getTextureID();
}
	
} // namespace
