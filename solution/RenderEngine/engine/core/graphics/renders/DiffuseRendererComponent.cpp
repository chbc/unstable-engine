#include "DiffuseRendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

DiffuseRendererComponent::DiffuseRendererComponent(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void DiffuseRendererComponent::setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram)
{
	this->shaderManager->setInt(shaderProgram, "diffuseTexture", 0);
	this->textureId = mesh->getMaterial()->getComponent<DiffuseMaterialComponent>()->getTextureID();
}

void DiffuseRendererComponent::preDraw()
{
	this->graphicsWrapper->enableTexCoords();
	this->graphicsWrapper->activeDiffuseTexture(this->textureId);
}

void DiffuseRendererComponent::postDraw()
{
	this->graphicsWrapper->disableTexCoords();
}

} // namespace
