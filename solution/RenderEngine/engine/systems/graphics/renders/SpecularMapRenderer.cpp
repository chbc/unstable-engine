#include "SpecularMapRenderer.h"

#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/meshes/materials/components/SpecularMaterialComponent.h>
#include <engine/systems/graphics/ShaderManager.h>

namespace sre
{

SpecularMapRenderer::SpecularMapRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: ColorRenderer(graphicsWrapper)
{ }

void SpecularMapRenderer::loadShader()
{
	this->shaderProgram = this->shaderManager->loadSpecularMapShader();
}

void SpecularMapRenderer::setupMaterial(MeshComponent *mesh)
{
	ColorRenderer::setupMaterial(mesh);
	this->shaderManager->setInt(this->shaderProgram, "diffuseTexture", 0);
	this->shaderManager->setInt(this->shaderProgram, "normalTexture", 1);
	this->shaderManager->setInt(this->shaderProgram, "specularTexture", 2);
}

void SpecularMapRenderer::drawMesh(MeshComponent *mesh)
{
	Material *material = mesh->getMaterial();
	DiffuseMaterialComponent *diffuseMaterial = material->getComponent<DiffuseMaterialComponent>();
	NormalMaterialComponent *normalMaterial = material->getComponent<NormalMaterialComponent>();
	SpecularMaterialComponent *specularMaterial = material->getComponent<SpecularMaterialComponent>();

	this->graphicsWrapper->drawSpecularNormalTexturedMesh
	(
		mesh, 
		diffuseMaterial->getTextureID(),
		normalMaterial->getTextureID(),
		specularMaterial->getTextureID()
	);
}

} // namespace
