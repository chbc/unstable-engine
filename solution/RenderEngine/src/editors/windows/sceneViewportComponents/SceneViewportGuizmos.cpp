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
}

void SceneViewportGuizmos::onInit()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<EntitySelectionMessage>(this->selectionAction.get());
	this->selectedEntity = nullptr;
	this->guizmoOperation = ImGuizmo::TRANSLATE;
}

bool SceneViewportGuizmos::drawAndManipulate(float windowWidth, float windowHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	bool result = false;

	if (this->selectedEntity != nullptr)
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();

		ImVec2 windowPosition = ImGui::GetWindowPos();
		ImGuizmo::SetRect(windowPosition.x, windowPosition.y, windowWidth, windowHeight);

		TransformComponent* entityTransform = this->selectedEntity->getTransform();
		glm::mat4 entityMatrix = entityTransform->getMatrix();

		ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
			this->guizmoOperation, ImGuizmo::LOCAL, glm::value_ptr(entityMatrix));

		if (ImGuizmo::IsUsing())
		{
			glm::vec3 position{ 0.0f }, scale{ 0.0f }, rotation{ 0.0f };
			MathUtils::decomposeTransform(entityMatrix, position, scale, rotation);

			entityTransform->setPosition(position);
			entityTransform->setScale(scale);
			entityTransform->setRotation(glm::degrees(rotation));

			result = true;
		}
	}

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
}

void SceneViewportGuizmos::onEntitySelected(void* data)
{
	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);
	this->selectedEntity = message->entity;

	GuizmoComponent* guizmoComponent = nullptr;
	if (this->selectedEntity != nullptr)
	{
		guizmoComponent = this->selectedEntity->getComponent<GuizmoComponent>();
	}

	RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
	renderManager->addGuizmoComponent(guizmoComponent);
}

} // namespace
