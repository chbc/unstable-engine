#include "GuizmoRenderer.h"
#include "AGraphicsWrapper.h"
#include "ShaderManager.h"
#include "CameraComponent.h"
#include "GuizmoComponent.h"
#include "TransformComponent.h"
#include "AColliderComponent.h"
#include "MeshComponent.h"
#include "AssetsManager.h"
#include "SingletonsManager.h"
#include "Entity.h"

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

void GuizmoRenderer::addGuizmos(Entity* entity)
{
	std::vector<GuizmoComponent*> guizmoComponents;
	entity->getComponents<GuizmoComponent>(guizmoComponents);
	AColliderComponent* collider = nullptr;

	for (GuizmoComponent* item : guizmoComponents)
	{
		switch (item->guizmoType)
		{
			case EGuizmoType::MESH:
				this->meshGuizmos.push_back(item);
				entity->getBounds(item->bounds);
				break;

			case EGuizmoType::BOX_COLLISION:
				collider = entity->getBaseComponent<AColliderComponent>();
				item->bounds = collider->getBounds();
				this->boxColliderGuizmos.push_back(item);
				break;

			case EGuizmoType::SPHERE_COLLISION:
				collider = entity->getBaseComponent<AColliderComponent>();
				item->bounds = collider->getBounds();
				this->sphereColliderGuizmos.push_back(item);
				break;
			default: break;
		}

		if (item->mesh->ebo == 0)
		{
			this->graphicsWrapper->createBuffers(item->mesh);

		}
	}
}

void GuizmoRenderer::loadShader()
{
    this->program = this->shaderManager->loadColorShader();
    this->shaderManager->setupAttributeLocation(this->program, ShaderVariables::IN_POSITION);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MATERIAL_COLOR);
	this->shaderManager->setupUniformLocation(this->program, ShaderVariables::MODEL_MATRIX);
}

void GuizmoRenderer::render()
{
	this->shaderManager->enableShader(this->program);

	for (GuizmoComponent* item : this->meshGuizmos)
	{
		this->renderMeshGuizmo(item);
	}

	/*
	for (GuizmoComponent* item : this->boxColliderGuizmos)
	{
		BoxColliderComponent* collider = item->getEntity()->getComponent<BoxColliderComponent>();
		if (collider)
		{
			this->renderColliderGuizmo(item, collider);
		}
	}
	*/
}

void GuizmoRenderer::renderMeshGuizmo(GuizmoComponent* guizmoComponent)
{
	Entity* entity = guizmoComponent->getEntity();
	TransformComponent* transform = entity->getTransform();
	const glm::mat4& modelMatrix = transform->getMatrix();
	glm::mat4 resultMatrix = glm::translate(modelMatrix, guizmoComponent->bounds.center);
	resultMatrix = glm::scale(resultMatrix, guizmoComponent->bounds.getSize());

	ColorMeshData* mesh = guizmoComponent->mesh;
	this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);
	this->graphicsWrapper->enableColorMeshSettings();

	this->shaderManager->setMat4(this->program, ShaderVariables::MODEL_MATRIX, &resultMatrix[0][0]);
	this->shaderManager->setVec4(this->program, ShaderVariables::MATERIAL_COLOR, &mesh->color[0]);
	this->graphicsWrapper->drawElement(mesh->ebo, mesh->indices.size(), EDrawMode::LINES);
	
	this->graphicsWrapper->disableColorMeshSettings();
}

/*
void GuizmoRenderer::renderColliderGuizmo(GuizmoComponent* guizmoComponent, AColliderComponent* collider)
{
	Entity* entity = guizmoComponent->getEntity();
	TransformComponent* transform = entity->getTransform();

	Bounds bounds = collider->getBounds();
	glm::vec3 position = transform->getPosition() + bounds.center;

	glm::mat4 modelMatrix{ 1.0f };
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, bounds.getSize());

	ColorMeshData* mesh = guizmoComponent->mesh;
	this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);
	this->graphicsWrapper->enableColorMeshSettings();

	glm::vec4 color = glm::vec4{ 0.25f, 1.0f, 0.25f, 1.0f };
	this->shaderManager->setMat4(this->program, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);
	this->shaderManager->setVec4(this->program, ShaderVariables::MATERIAL_COLOR, &color[0]);
	this->graphicsWrapper->drawElement(mesh->ebo, mesh->indices.size(), EDrawMode::LINES);

	this->graphicsWrapper->disableColorMeshSettings();
}
*/
void GuizmoRenderer::removeGuizmos(Entity* entity)
{
	std::vector<GuizmoComponent*> guizmoComponents;
	entity->getComponents<GuizmoComponent>(guizmoComponents);

	for (GuizmoComponent* item : guizmoComponents)
	{
		switch (item->guizmoType)
		{
			case EGuizmoType::MESH:
				this->meshGuizmos.remove(item);
				break;
			case EGuizmoType::BOX_COLLISION:
				this->boxColliderGuizmos.remove(item);
				break;
			case EGuizmoType::SPHERE_COLLISION:
				this->sphereColliderGuizmos.remove(item);
				break;
			default: break;
		}
	}
}

} // namespace
