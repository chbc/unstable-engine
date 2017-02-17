#include "AOMapRenderer.h"

#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/meshes/materials/components/AmbientOcclusionMaterialComponent.h>
#include <engine/systems/graphics/ShaderManager.h>

namespace sre
{

AOMapRenderer::AOMapRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper)
	: ColorRenderer(graphicsWrapper)
{ }

void AOMapRenderer::loadShader()
{
	this->shaderProgram = this->shaderManager->loadAOMapShader();
}

void AOMapRenderer::setupMaterial(MeshComponent *mesh)
{
	ColorRenderer::setupMaterial(mesh);
	this->shaderManager->setInt(this->shaderProgram, "diffuseTexture", 0);
	this->shaderManager->setInt(this->shaderProgram, "normalTexture", 1);
	this->shaderManager->setInt(this->shaderProgram, "specularTexture", 2);
	this->shaderManager->setInt(this->shaderProgram, "aoTexture", 3);
}

void AOMapRenderer::drawMesh(MeshComponent *mesh)
{
	Material *material = mesh->getMaterial();
	DiffuseMaterialComponent *diffuseMaterial = material->getComponent<DiffuseMaterialComponent>();
	NormalMaterialComponent *normalMaterial = material->getComponent<NormalMaterialComponent>();
	SpecularMaterialComponent *specularMaterial = material->getComponent<SpecularMaterialComponent>();
	AmbientOcclusionMaterialComponent *aoMaterial = material->getComponent<AmbientOcclusionMaterialComponent>();

	this->graphicsWrapper->drawAOSpecularNormalTexturedMesh
	(
		mesh, 
		diffuseMaterial->getTextureID(),
		normalMaterial->getTextureID(),
		specularMaterial->getTextureID(),
		aoMaterial->getTextureID()
	);
}

} // namespace
