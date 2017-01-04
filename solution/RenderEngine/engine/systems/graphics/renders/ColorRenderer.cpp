#include "ColorRenderer.h"

#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/systems/graphics/MatrixManager.h>
#include <engine/systems/graphics/ShaderManager.h>
#include <engine/systems/wrappers/graphics/OpenGLAPI.h>
#include <engine/systems/graphics/ShaderManager.h>
#include "ShaderConsts.h"

namespace sre
{

ColorRenderer::ColorRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper)
{
	this->graphicsWrapper = graphicsWrapper;
	this->shaderManager	= UPTR<ShaderManager>{ new ShaderManager{graphicsWrapper} };
	this->shaderPorgram = this->shaderManager->loadShader(ShaderConsts::COLOR_V, ShaderConsts::COLOR_F);
    this->vertexAttribLocation = this->shaderManager->getAttribLocation(this->shaderPorgram, EShaderVariable::SHADER_POSITION);
    this->normalAttribLocation = this->shaderManager->getAttribLocation(this->shaderPorgram, EShaderVariable::SHADER_NORMAL);
}

ColorRenderer::~ColorRenderer()
{
	this->meshes.clear();
}

void ColorRenderer::addMesh(MeshComponent *mesh)
{
	this->meshes.push_back(mesh);
}

void ColorRenderer::createVBO(MeshComponent *mesh)
{
	this->graphicsWrapper->createVBO(mesh);
	this->graphicsWrapper->createIBO(mesh);
}

uint32_t ColorRenderer::loadShader(const std::string &vertFile, const std::string &fragFile)
{
	return this->shaderManager->loadShader(vertFile, fragFile);
}

void ColorRenderer::render(MatrixManager *matrixManager, AGraphicsWrapper *graphicsWrapper)
{
	// Shader setup
	this->shaderManager->enableShader(this->shaderPorgram);

	glm::mat4 viewProjectionMatrix = matrixManager->getViewProjectionMatrix();
	this->shaderManager->setValue(this->shaderPorgram, "viewProjectionMatrix", &viewProjectionMatrix[0][0]);

	// ### tratar os filhos das entidades
	for (MeshComponent *mesh : this->meshes)
	{
		// Matrix setup
		TransformComponent *transform = mesh->getTransform();
		matrixManager->push(transform->getMatrix());

		glm::mat4 modelMatrix = matrixManager->getModelMatrix();
		this->shaderManager->setValue(this->shaderPorgram, "modelMatrix", &modelMatrix[0][0]);

		ColorMaterialComponent *colorMaterial = mesh->material->getComponent<ColorMaterialComponent>();
		glm::vec4 color = colorMaterial->getColor();
		this->shaderManager->setValue(this->shaderPorgram, "materialColor", color.r, color.g, color.b, color.a);

		/* ###
		if (receiveLight)
			lightManager->setupLights(shaderProgram);
		*/

		graphicsWrapper->drawMesh(mesh, this->vertexAttribLocation, this->normalAttribLocation);
		matrixManager->pop();
	}

	this->shaderManager->disableShader();
}

}
