#include "DiffuseTexturedRenderer.h"

#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/meshes/materials/components/DiffuseMaterialComponent.h>

namespace sre
{

void DiffuseTexturedRenderer::drawMesh(MeshComponent *mesh)
{
	DiffuseMaterialComponent *diffuseMaterial = mesh->getMaterial()->getComponent<DiffuseMaterialComponent>();
	this->graphicsWrapper->drawTexturedMesh(mesh, diffuseMaterial->getTextureID());  // ###
}

} // namespace
