#include "SceneViewportGuizmos.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "RenderManager.h"
#include "MathUtils.h"
#include "Entity.h"
#include "GuizmoComponent.h"

#include <imgui/imgui.h>
#include <imguizmo/ImGuizmo.h>
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

SceneViewportGuizmos::SceneViewportGuizmos()
{
	Action* action = new Action{ [&](void* message) { this->onEntitySelected(message); } };
	this->selectionAction = SPTR<Action>(action);
	this->orientationModeAction = SPTR<Action>(new Action{ [&](void* message) { this->onOrientationModeChanged(message); } });
}

void SceneViewportGuizmos::onInit()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<EntitySelectionMessage>(this->selectionAction.get());
	messagesManager->addListener<ChangeGuizmoModeMessage>(this->orientationModeAction.get());
	this->selectedEntity = nullptr;
	this->guizmoOperation = ImGuizmo::TRANSLATE;
	
	this->guizmoEntity = new Entity("Guizmo");
	this->guizmoEntity->addComponent<GuizmoComponent>();
}

bool SceneViewportGuizmos::drawAndManipulate(bool cameraMoving, const glm::vec2& windowPos, const glm::vec2& windowSize, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	bool result = false;

	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(windowPos.x, windowPos.y, windowSize.x, windowSize.y);

	if (!cameraMoving && this->selectedEntity)
	{
		TransformComponent* entityTransform = this->selectedEntity->getTransform();
		glm::mat4 entityMatrix = entityTransform->getMatrix();

		ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
			this->guizmoOperation, this->guizmoMode, glm::value_ptr(entityMatrix));

		if (ImGuizmo::IsUsing())
		{
			glm::vec3 position{ 0.0f }, scale{ 0.0f }, rotation{ 0.0f };
			MathUtils::decomposeTransform(entityMatrix, position, scale, rotation);

			entityTransform->setPosition(position);
			entityTransform->setScale(scale);
			entityTransform->setRotation(glm::degrees(rotation));

			result = true;

			this->onEntityManipulated();
		}
	}

	static const glm::mat4 identityMatrix{ 1.0f };
	ImGuizmo::DrawGrid(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix), glm::value_ptr(identityMatrix), 20.0f);

	return result;
}

void SceneViewportGuizmos::processGuizmoOperationSelection()
{
	if (ImGui::IsKeyPressed(ImGuiKey_W))
	{
		this->guizmoOperation = ImGuizmo::TRANSLATE;
	}
	else if (ImGui::IsKeyPressed(ImGuiKey_E))
	{
		this->guizmoOperation = ImGuizmo::ROTATE;
	}
	else if (ImGui::IsKeyPressed(ImGuiKey_R))
	{
		this->guizmoOperation = ImGuizmo::SCALE;
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
	this->guizmoEntity->removeFromParent();

	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);
	this->selectedEntity = message->entity;

	GuizmoComponent* guizmoComponent = nullptr;
	if (this->selectedEntity != nullptr)
	{
		this->selectedEntity->addChild(this->guizmoEntity);
		guizmoComponent = this->guizmoEntity->getComponent<GuizmoComponent>();
	}

	RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
	renderManager->addGuizmoComponent(guizmoComponent);
}

void SceneViewportGuizmos::onEntityManipulated()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->notify<EntityChangedEditorMessage>();
}

void SceneViewportGuizmos::onOrientationModeChanged(void* message)
{
	ChangeGuizmoModeMessage* orientationMessage = static_cast<ChangeGuizmoModeMessage*>(message);
	this->guizmoMode = static_cast<ImGuizmo::MODE>(orientationMessage->mode);
}

} // namespace
