#include "GUIRenderer.h"

#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/entities/components/gui/GUIImageComponent.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/core/graphics/MatrixManager.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/multimedia/textures/Texture.h>

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

void GUIRenderer::addDynamicGUIComponent(GUIImageComponent *guiComponent)
{
	this->dynamicGUIComponents.push_back(guiComponent);
	this->graphicsWrapper->createGUIVAO(guiComponent);
	this->graphicsWrapper->createGUIEBO(guiComponent);
}

void GUIRenderer::removeGUIComponent(GUIImageComponent *guiComponent)
{
	this->guiComponents.remove(guiComponent);
}

void GUIRenderer::render(MatrixManager *matrixManager)
{
	this->shaderManager->enableShader(this->shaderProgram);
	this->shaderManager->setInt(shaderProgram, "guiTexture", 0);

	// Static meshes
	for (GUIImageComponent *item : this->guiComponents)
	{
		this->setup(item);
		this->graphicsWrapper->drawElement(item->meshData->indices.size());
	}

	// Dynamic meshes
	for (GUIImageComponent *item : this->dynamicGUIComponents)
	{
		this->setup(item);
		this->graphicsWrapper->drawElement(item->meshData->indices.size());
	}

	this->graphicsWrapper->disableGUISettings();
	this->shaderManager->disableShader();
}

void GUIRenderer::setup(GUIImageComponent *guiComponent)
{
	// Matrix setup
	TransformComponent *transform = guiComponent->getTransform();
	glm::mat4 modelMatrix = transform->getMatrix();
	this->shaderManager->setMat4(this->shaderProgram, "modelMatrix", &modelMatrix[0][0]);

	this->graphicsWrapper->bindVAO(guiComponent->vao, guiComponent->vbo);
	this->graphicsWrapper->enableGUISettings();
	this->graphicsWrapper->activeDiffuseTexture(guiComponent->getTextureId());
}

} // namespace
