#include "GUIRenderer.h"

#include <engine/entities/components/gui/GUIImageComponent.h>
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/systems/graphics/MatrixManager.h>
#include <engine/systems/graphics/ShaderManager.h>
#include <engine/entities/components/meshes/materials/textures/Texture.h>

namespace sre
{

GUIRenderer::GUIRenderer(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper)
{
	this->shaderManager = shaderManager;
	this->graphicsWrapper = graphicsWrapper;
}

void GUIRenderer::loadShader()
{
	this->shaderProgram = this->shaderManager->loadGUIShader();
}

void GUIRenderer::addGUIComponent(GUIImageComponent *guiComponent)
{
	this->guiComponents.push_back(guiComponent);
	this->graphicsWrapper->createGUIVAO(guiComponent);
	this->graphicsWrapper->createGUIEBO(guiComponent);
}

void GUIRenderer::removeGUIComponent(GUIImageComponent *guiComponent)
{
	this->guiComponents.remove(guiComponent);
}

void GUIRenderer::render()
{
	this->shaderManager->enableShader(this->shaderProgram);

	for (GUIImageComponent *item : this->guiComponents)
	{
		this->graphicsWrapper->bindVAO(item->vao, item->vbo);

		this->shaderManager->setInt(shaderProgram, "guiTexture", 0);

		this->graphicsWrapper->enableGUISettings();

		this->graphicsWrapper->activeDiffuseTexture(item->texture->getId());

		this->graphicsWrapper->drawElement(item->vao, item->indices.size());
	}

	this->graphicsWrapper->disableGUISettings();
	this->shaderManager->disableShader();
}

} // namespace
