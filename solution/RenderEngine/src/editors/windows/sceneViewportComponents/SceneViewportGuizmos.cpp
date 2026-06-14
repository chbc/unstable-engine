#include "SceneViewportGuizmos.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "RenderManager.h"
#include "MathUtils.h"
#include "Entity.h"
#include "GuizmoComponent.h"
#include "AColliderComponent.h"

#include "imgui.h"
#include "ImGuizmo.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


namespace sre
{

ImGuizmo::OPERATION toImGuizmoOperation(sre::EGuizmoOperation operation)
{
	switch (operation)
	{
		case EGuizmoOperation::TRANSLATE: return ImGuizmo::TRANSLATE;
		case EGuizmoOperation::ROTATE: return ImGuizmo::ROTATE;
		case EGuizmoOperation::SCALE: return ImGuizmo::SCALE;
		default: return ImGuizmo::TRANSLATE;
	}
}

ImGuizmo::MODE toImGuizmoMode(sre::EGuizmoMode mode)
{
	switch (mode)
	{
		case EGuizmoMode::LOCAL: return ImGuizmo::LOCAL;
		case EGuizmoMode::WORLD: return ImGuizmo::WORLD;
		default: return ImGuizmo::LOCAL;
	}
}
	
SceneViewportGuizmos::SceneViewportGuizmos()
{
	this->selectionAction = SPTR<Action>(new Action{ [&](void* message) { this->onEntitySelected(message); } });
	this->orientationModeAction = SPTR<Action>(new Action{ [&](void* message) { this->onOrientationModeChanged(message); } });
}

void SceneViewportGuizmos::onInit()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<EntitySelectionMessage>(this->selectionAction.get());
	messagesManager->addListener<ChangeGuizmoModeMessage>(this->orientationModeAction.get());
	this->selectedEntity = nullptr;
	this->guizmoOperation = EGuizmoOperation::TRANSLATE;

	ImGuizmo::AllowAxisFlip(false);
}

bool SceneViewportGuizmos::drawAndManipulate(bool cameraMoving, const glm::vec2& windowPos, const glm::vec2& windowSize, glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	bool result = false;

	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(windowPos.x, windowPos.y, windowSize.x, windowSize.y);

	if (!cameraMoving && this->selectedEntity)
	{
		TransformComponent* entityTransform = this->selectedEntity->getTransform();
		glm::mat4 entityMatrix = entityTransform->getMatrix();

		ImGuizmo::OPERATION operation = toImGuizmoOperation(this->guizmoOperation);
		ImGuizmo::MODE mode = toImGuizmoMode(this->guizmoMode);
		ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
			operation, mode, glm::value_ptr(entityMatrix));

		if (ImGuizmo::IsUsing())
		{
			entityTransform->setWorldMatrix(entityMatrix);

			result = true;

			entityTransform->onPropertyChanged();
		}
	}

	ImGuizmo::ViewManipulate
	(
		glm::value_ptr(viewMatrix), 10.0f,
		ImVec2(windowPos.x + windowSize.x - 128.0f, windowPos.y),
		ImVec2(128.0f, 128.0f),
		0x10101010
	);

	return result;
}

void SceneViewportGuizmos::processGuizmoOperationSelection()
{
	if (ImGui::IsKeyPressed(ImGuiKey_W))
	{
		this->guizmoOperation = EGuizmoOperation::TRANSLATE;
	}
	else if (ImGui::IsKeyPressed(ImGuiKey_E))
	{
		this->guizmoOperation = EGuizmoOperation::ROTATE;
	}
	else if (ImGui::IsKeyPressed(ImGuiKey_R))
	{
		this->guizmoOperation = EGuizmoOperation::SCALE;
	}
}

void SceneViewportGuizmos::onCleanUp()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->removeListener<EntitySelectionMessage>(this->selectionAction.get());
	messagesManager->removeListener<ChangeGuizmoModeMessage>(this->orientationModeAction.get());
}

void SceneViewportGuizmos::onEntitySelected(void* data)
{
	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);

	if (this->selectedEntity != message->entity)
	{
		RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
		if (this->selectedEntity)
		{
			renderManager->removeGuizmos(this->selectedEntity);
			this->selectedEntity->removeComponents<GuizmoComponent>(true);
		}

		this->selectedEntity = message->entity;

		if (this->selectedEntity)
		{
			this->addGuizmosToSelectedEntity();
			renderManager->addGuizmos(this->selectedEntity);
		}
	}
}

void SceneViewportGuizmos::onOrientationModeChanged(void* message)
{
	ChangeGuizmoModeMessage* orientationMessage = static_cast<ChangeGuizmoModeMessage*>(message);
	this->guizmoMode = static_cast<EGuizmoMode>(orientationMessage->mode);
}

void SceneViewportGuizmos::addGuizmosToSelectedEntity()
{
	GuizmoComponent* guizmoComponent = this->selectedEntity->addComponent<GuizmoComponent>();
	guizmoComponent->loadMesh(EGuizmoType::MESH);

	std::vector<AColliderComponent*> colliderComponents;
	this->selectedEntity->getBaseComponents<AColliderComponent>(colliderComponents);
	if (!colliderComponents.empty())
	{
		for (AColliderComponent* collider : colliderComponents)
		{
			Entity* entity = collider->getEntity();
			GuizmoComponent* guizmoComponent = entity->addComponent<GuizmoComponent>();
			switch (collider->getCollisionType())
			{
				case ECollisionType::BOX:
					guizmoComponent->loadMesh(EGuizmoType::BOX_COLLISION, collider);
					break;
				case ECollisionType::SPHERE:
					guizmoComponent->loadMesh(EGuizmoType::SPHERE_COLLISION, collider);
					break;
				default: break;
			}
		}
	}
}

} // namespace
