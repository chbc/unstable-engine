#include "GuizmoRenderer.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "CameraComponent.h"
#include "GuizmoComponent.h"
#include "TransformComponent.h"
#include "AssetsManager.h"
#include "SingletonsManager.h"

namespace sre
{

GuizmoRenderer::GuizmoRenderer(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
	: shaderManager(shaderManager), graphicsWrapper(graphicsWrapper)
{
	this->assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
}

GuizmoRenderer::~GuizmoRenderer()
{
	if (this->shaderManager != nullptr)
	{
		this->shaderManager->releaseShader(this->program);
	}
}

void GuizmoRenderer::addGuizmo(GuizmoComponent* guizmoComponent)
{
	this->guizmoComponents.clear();

	if (guizmoComponent != nullptr)
	{
		this->guizmoComponents.push_back(guizmoComponent);

		guizmoComponent->mesh = this->assetsManager->loadGuizmo(guizmoComponent->guizmoType);
		if (guizmoComponent->mesh->ebo == 0)
		{
			this->graphicsWrapper->createBuffers(guizmoComponent->mesh);
		}

		guizmoComponent->bounds.reset();

		Entity* parentEntity = guizmoComponent->getEntity()->getParent();
		parentEntity->getBounds(guizmoComponent->bounds);
	}
}

void GuizmoRenderer::loadShader()
{
    this->program = this->shaderManager->loadColorShader();
    this->shaderManager->setupAttributeLocation(this->program, ShaderVariables::IN_POSITION);
    this->shaderManager->setupUniformLocation(this->program, ShaderVariables::VIEW_MATRIX);
    this->shaderManager->setupUniformLocation(this->program, ShaderVariables::PROJECTION_MATRIX);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MATERIAL_COLOR);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MODEL_MATRIX);
}

void GuizmoRenderer::render(CameraComponent* camera)
{
    const glm::mat4& viewMatrix = camera->getViewMatrix();
    const glm::mat4& projectionMatrix = camera->getProjectionMatrix();

	this->shaderManager->enableShader(this->program);

    this->shaderManager->setMat4(this->program, ShaderVariables::VIEW_MATRIX, &viewMatrix[0][0]);
	this->shaderManager->setMat4(this->program, ShaderVariables::PROJECTION_MATRIX, &projectionMatrix[0][0]);

	for (GuizmoComponent* item : this->guizmoComponents)
	{
		ColorMeshData* mesh = item->mesh;
        this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);
        this->graphicsWrapper->enableColorMeshSettings();

		TransformComponent* transform = item->getTransform();
		const glm::mat4& modelMatrix = transform->getMatrix();
		glm::mat4 resultMatrix = glm::scale(modelMatrix, item->bounds.size);

		this->shaderManager->setMat4(this->program, ShaderVariables::MODEL_MATRIX, &resultMatrix[0][0]);
		this->shaderManager->setVec4(this->program, ShaderVariables::MATERIAL_COLOR, &mesh->color[0]);
		this->graphicsWrapper->drawElement(mesh->ebo, mesh->indices.size(), EDrawMode::LINES);

		this->graphicsWrapper->disableColorMeshSettings();
	}
}

} // namespace
