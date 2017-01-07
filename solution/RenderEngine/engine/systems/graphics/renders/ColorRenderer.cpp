#include "ColorRenderer.h"

#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/systems/graphics/MatrixManager.h>
#include <engine/systems/graphics/ShaderManager.h>
#include <engine/systems/graphics/LightManager.h>
#include <engine/systems/wrappers/graphics/OpenGLAPI.h>
#include "ShaderConsts.h"

namespace sre
{

ColorRenderer::ColorRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper)
{
	this->graphicsWrapper = graphicsWrapper;
	this->shaderManager	= UPTR<ShaderManager>{ new ShaderManager{graphicsWrapper} };
	this->shaderProgram = this->shaderManager->loadShader(ShaderConsts::COLOR_V, ShaderConsts::COLOR_F);
    this->vertexAttribLocation = this->shaderManager->getAttribLocation(this->shaderProgram, EShaderVariable::SHADER_POSITION);
    this->normalAttribLocation = this->shaderManager->getAttribLocation(this->shaderProgram, EShaderVariable::SHADER_NORMAL);
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

		ColorMaterialComponent *colorMaterial = mesh->material->getComponent<ColorMaterialComponent>();
		glm::vec4 color = colorMaterial->getColor();
		this->shaderManager->setVec4(this->shaderProgram, "materialColor", &color[0]);

		this->graphicsWrapper->drawMesh(mesh, this->vertexAttribLocation, this->normalAttribLocation);
		matrixManager->pop();
	}

	this->shaderManager->disableShader();
}

} // namespace
