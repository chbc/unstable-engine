#include "DebugRenderer.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "CameraComponent.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

DebugRenderer::DebugRenderer(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
	: shaderManager(shaderManager), graphicsWrapper(graphicsWrapper)
{ }

DebugRenderer::~DebugRenderer()
{
	if (this->shaderManager != nullptr)
	{
		this->shaderManager->releaseShader(this->program);
	}
}

void DebugRenderer::addBox(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	ColorMeshData* meshData = PrimitiveMeshFactory().createBoxLines(position, size, color);
	this->graphicsWrapper->createBuffers(meshData);
	this->meshes.emplace_back(meshData);
}

void DebugRenderer::loadShader()
{
    this->program = this->shaderManager->loadColorShader();
    this->shaderManager->setupAttributeLocation(this->program, ShaderVariables::IN_POSITION);
    this->shaderManager->setupUniformLocation(this->program, ShaderVariables::VIEW_MATRIX);
    this->shaderManager->setupUniformLocation(this->program, ShaderVariables::PROJECTION_MATRIX);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MATERIAL_COLOR);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MODEL_MATRIX);
}

void DebugRenderer::render(CameraComponent* camera)
{
    const glm::mat4& viewMatrix = camera->getViewMatrix();
    const glm::mat4& projectionMatrix = camera->getProjectionMatrix();

	this->shaderManager->enableShader(this->program);

    this->shaderManager->setMat4(this->program, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
	this->shaderManager->setMat4(this->program, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);

	for (const UPTR<ColorMeshData>& item : this->meshes)
	{
        this->graphicsWrapper->bindVAO(item->vao, item->vbo);
        this->graphicsWrapper->enableColorMeshSettings();

		glm::mat4 modelMatrix{ 1.0f };
		this->shaderManager->setMat4(this->program, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);
		this->shaderManager->setVec4(this->program, ShaderVariables::MATERIAL_COLOR, &item->color[0]);
		this->graphicsWrapper->drawElement(item->ebo, item->indices.size(), EDrawMode::LINES);

		this->graphicsWrapper->disableColorMeshSettings();
	}
}

} // namespace
