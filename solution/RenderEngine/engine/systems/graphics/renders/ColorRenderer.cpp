#include "ColorRenderer.h"

#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/systems/graphics/MatrixManager.h>
#include <engine/systems/graphics/ShaderManager.h>
#include <engine/systems/graphics/LightManager.h>
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

ColorRenderer::ColorRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper)
{
	this->graphicsWrapper = graphicsWrapper;
	this->shaderManager	= UPTR<ShaderManager>{ new ShaderManager{graphicsWrapper} };
}

ColorRenderer::~ColorRenderer()
{
	this->meshes.clear();
}

void ColorRenderer::loadShader()
{
	this->shaderProgram = shaderManager->loadColorShader();
}

void ColorRenderer::setupMaterial(MeshComponent *mesh)
{
	ColorMaterialComponent *colorMaterial = mesh->getMaterial()->getComponent<ColorMaterialComponent>();
	glm::vec4 color = colorMaterial->getColor();
	this->shaderManager->setVec4(this->shaderProgram, "materialColor", &color[0]);
	this->shaderManager->setFloat(this->shaderProgram, "shininess", mesh->getMaterial()->getShininess());
}

void ColorRenderer::addMesh(MeshComponent *mesh)
{
	this->meshes.push_back(mesh);
}

void ColorRenderer::removeMesh(MeshComponent *mesh)
{
	this->meshes.remove(mesh);
}

void ColorRenderer::createVBO(MeshComponent *mesh)
{
	this->graphicsWrapper->createVBO(mesh);
	this->graphicsWrapper->createIBO(mesh);
}

void ColorRenderer::render(MatrixManager *matrixManager, LightManager *lightManager, const glm::vec3 &cameraPosition)
{
	// Shader setup
	this->shaderManager->enableShader(this->shaderProgram);

	glm::mat4 viewMatrix = matrixManager->getViewMatrix();
	glm::mat4 projectionMatrix = matrixManager->getProjectionMatrix();

	// ### obter a localização das variáveis do shader
	this->shaderManager->setMat4(this->shaderProgram, "viewMatrix", &viewMatrix[0][0]);
	this->shaderManager->setMat4(this->shaderProgram, "projectionMatrix", &projectionMatrix[0][0]);
	this->shaderManager->setVec3(this->shaderProgram, "cameraPosition", &cameraPosition[0]);
	
	lightManager->setupLights(this->shaderManager.get(), this->shaderProgram);

	// ### tratar os filhos das entidades
	for (MeshComponent *mesh : this->meshes)
	{
		// Matrix setup
		TransformComponent *transform = mesh->getTransform();
		matrixManager->push(transform->getMatrix());

		glm::mat4 modelMatrix = matrixManager->getModelMatrix();
		this->shaderManager->setMat4(this->shaderProgram, "modelMatrix", &modelMatrix[0][0]);

		this->setupMaterial(mesh);
		this->drawMesh(mesh);

		matrixManager->pop();
	}

	this->shaderManager->disableShader();
}

void ColorRenderer::drawMesh(MeshComponent *mesh)
{
	this->graphicsWrapper->drawColorMesh(mesh);
}

bool ColorRenderer::contains(MeshComponent *mesh)
{
	bool result = false;

	for (MeshComponent *item : this->meshes)
	{
		if (item == mesh)
		{
			result = true;
			break;
		}
	}

	return result;
}

} // namespace
