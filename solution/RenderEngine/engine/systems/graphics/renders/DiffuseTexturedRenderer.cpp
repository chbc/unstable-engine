#include "DiffuseTexturedRenderer.h"

#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/meshes/materials/components/DiffuseMaterialComponent.h>
#include <engine/systems/graphics/ShaderManager.h>

namespace sre
{

DiffuseTexturedRenderer::DiffuseTexturedRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: ColorRenderer(graphicsWrapper)
{ }

void DiffuseTexturedRenderer::loadShader()
{
	this->shaderProgram = this->shaderManager->loadDiffuseShader();
}

void DiffuseTexturedRenderer::drawMesh(MeshComponent *mesh)
{
	DiffuseMaterialComponent *diffuseMaterial = mesh->getMaterial()->getComponent<DiffuseMaterialComponent>();
	this->graphicsWrapper->drawTexturedMesh(mesh, diffuseMaterial->getTextureID());  // ###
}

} // namespace
