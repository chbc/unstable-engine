#include "NormalMapRenderer.h"

#include <engine/systems/graphics/ShaderManager.h>

namespace sre
{

NormalMapRenderer::NormalMapRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: ColorRenderer(graphicsWrapper)
{ }

void NormalMapRenderer::loadShader()
{
	this->shaderProgram = this->shaderManager->loadDiffuseShader();
}

void NormalMapRenderer::drawMesh(MeshComponent *mesh)
{
	/*
	DiffuseMaterialComponent *diffuseMaterial = mesh->getMaterial()->getComponent<DiffuseMaterialComponent>();
	this->graphicsWrapper->drawTexturedMesh(mesh, diffuseMaterial->getTextureID());  // ###
	*/
}

} // namespace
