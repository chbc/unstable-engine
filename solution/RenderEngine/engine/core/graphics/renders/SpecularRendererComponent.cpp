#include "SpecularRendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

SpecularRendererComponent::SpecularRendererComponent(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void SpecularRendererComponent::setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram)
{
	this->shaderManager->setInt(shaderProgram, "specularTexture", 2);
	this->textureId = mesh->getMaterial()->getComponent<SpecularMaterialComponent>()->getTextureID();
}

void SpecularRendererComponent::preDraw()
{
	this->graphicsWrapper->enableTexCoords();
	this->graphicsWrapper->activeSpecularTexture(this->textureId);
}

void SpecularRendererComponent::postDraw()
{
	this->graphicsWrapper->disableTexCoords();
}

} // namespace
