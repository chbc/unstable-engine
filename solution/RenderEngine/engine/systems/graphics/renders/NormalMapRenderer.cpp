#include "NormalMapRenderer.h"
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/meshes/materials/components/NormalMaterialComponent.h>
#include <engine/systems/graphics/ShaderManager.h>

namespace sre
{

NormalMapRenderer::NormalMapRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: ColorRenderer(graphicsWrapper)
{ }

void NormalMapRenderer::loadShader()
{
	this->shaderProgram = this->shaderManager->loadNormalMapShader();
}

void NormalMapRenderer::setupMaterial(MeshComponent *mesh)
{
	ColorRenderer::setupMaterial(mesh);
	this->shaderManager->setInt(this->shaderProgram, "diffuseTexture", 0);
	this->shaderManager->setInt(this->shaderProgram, "normalTexture", 1);
}

void NormalMapRenderer::drawMesh(MeshComponent *mesh)
{
	Material *material = mesh->getMaterial();
	DiffuseMaterialComponent *diffuseMaterial = material->getComponent<DiffuseMaterialComponent>();
	NormalMaterialComponent *normalMaterial = material->getComponent<NormalMaterialComponent>();
	
	this->graphicsWrapper->drawNormalTexturedMesh
	(
		mesh, 
		diffuseMaterial->getTextureID(),
		normalMaterial->getTextureID()
	);
}

} // namespace
