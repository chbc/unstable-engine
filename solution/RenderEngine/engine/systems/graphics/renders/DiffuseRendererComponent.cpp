#include "DiffuseRendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/systems/graphics/ShaderManager.h>
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

DiffuseRendererComponent::DiffuseRendererComponent(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void DiffuseRendererComponent::setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram)
{
	ColorRendererComponent::setupShaderVariables(mesh, shaderProgram);
	this->shaderManager->setInt(shaderProgram, "diffuseTexture", 0);
	this->textureId = mesh->getMaterial()->getComponent<DiffuseMaterialComponent>()->getTextureID();
}

void DiffuseRendererComponent::preDraw()
{
	ColorRendererComponent::preDraw();
	this->graphicsWrapper->enableTexCoords();
	this->graphicsWrapper->activeDiffuseTexture(this->textureId);
}

void DiffuseRendererComponent::postDraw()
{
	ColorRendererComponent::postDraw();
	this->graphicsWrapper->disableTexCoords();
}

} // namespace
