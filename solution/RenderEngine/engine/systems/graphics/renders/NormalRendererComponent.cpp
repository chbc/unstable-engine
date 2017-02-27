#include "NormalRendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/systems/graphics/ShaderManager.h>
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

NormalRendererComponent::NormalRendererComponent(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void NormalRendererComponent::setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram)
{
	this->shaderManager->setInt(shaderProgram, "normalTexture", 1);
	this->textureId = mesh->getMaterial()->getComponent<NormalMaterialComponent>()->getTextureID();
}

void NormalRendererComponent::preDraw()
{
	this->graphicsWrapper->enableVertexTangents();
	this->graphicsWrapper->enableVertexBitangents();
	this->graphicsWrapper->activeNormalTexture(this->textureId);
}

void NormalRendererComponent::postDraw()
{
	this->graphicsWrapper->disableVertexTangents();
	this->graphicsWrapper->disableVertexBitangents();
}

} // namespace
