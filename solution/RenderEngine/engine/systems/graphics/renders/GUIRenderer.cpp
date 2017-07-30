#include "GUIRenderer.h"

#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/entities/components/gui/GUIImageComponent.h>
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include <engine/systems/graphics/MatrixManager.h>
#include <engine/systems/graphics/ShaderManager.h>
#include <engine/systems/multimedia/textures/Texture.h>

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

void GUIRenderer::render(MatrixManager *matrixManager)
{
	this->shaderManager->enableShader(this->shaderProgram);

	glm::mat4 projectionMatrix = matrixManager->getProjectionMatrix();

	for (GUIImageComponent *item : this->guiComponents)
	{
		// Matrix setup
		TransformComponent *transform = item->getTransform();
		glm::mat4 modelMatrix = transform->getMatrix();
		this->shaderManager->setMat4(this->shaderProgram, "modelMatrix", &modelMatrix[0][0]);

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
