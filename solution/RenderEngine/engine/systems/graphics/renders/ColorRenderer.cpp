#include "ColorRenderer.h"

#include <engine/entities/components/transforms/TransformComponent.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/systems/graphics/MatrixManager.h>
#include <engine/systems/graphics/ShaderManager.h>
#include <engine/systems/wrappers/graphics/OpenGLAPI.h>

namespace sre
{

ColorRenderer::ColorRenderer()
{
}

ColorRenderer::~ColorRenderer()
{
	this->meshes.clear();
}

void ColorRenderer::addMesh(MeshComponent *mesh)
{
	this->meshes.push_back(mesh);
}

void ColorRenderer::render(MatrixManager *matrixManager, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
{
	for (MeshComponent *mesh : this->meshes)
	{
		// Matrix setup
		TransformComponent *transform = mesh->getTransform();
		matrixManager->push(transform->getMatrix());
		matrixManager->update();

		// Shader setup
		uint32_t shaderProgram = mesh->material->getShaderProgram();
		shaderManager->enableShader(shaderProgram);

		glm::mat4 mvp = matrixManager->getMVP();
		shaderManager->setValue(shaderProgram, "MVP", &mvp[0][0]);

		glm::mat4 modelMatrix = matrixManager->getModelMatrix();
		shaderManager->setValue(shaderProgram, "modelMatrix", &modelMatrix[0][0]);

		ColorMaterialComponent *colorMaterial = mesh->material->getComponent<ColorMaterialComponent>();
		glm::vec4 color = colorMaterial->getColor();
		shaderManager->setValue(shaderProgram, "materialColor", color.r, color.g, color.b, color.a);

		/* ###
		if (receiveLight)
			lightManager->setupLights(shaderProgram);
		*/

		graphicsWrapper->drawMesh(mesh);
		shaderManager->disableShader();

		matrixManager->pop();
	}

}

}
