#include "AORendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

AORendererComponent::AORendererComponent(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: DiffuseRendererComponent(shaderManager, graphicsWrapper)
{ }

void AORendererComponent::setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram)
{
	this->shaderManager->setInt(shaderProgram, "aoTexture", 3);
	this->textureId = mesh->getMaterial()->getComponent<AmbientOcclusionMaterialComponent>()->getTextureID();
}

void AORendererComponent::preDraw()
{
	this->graphicsWrapper->enableTexCoords();
	this->graphicsWrapper->activeAOTexture(this->textureId);
}

void AORendererComponent::postDraw()
{
	this->graphicsWrapper->disableTexCoords();
}

} // namespace
