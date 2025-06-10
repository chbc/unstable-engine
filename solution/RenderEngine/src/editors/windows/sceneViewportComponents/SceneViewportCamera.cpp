#include "SceneViewportCamera.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "FlyingMovementComponent.h"
#include "OrbitMovementComponent.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "EngineValues.h"
#include "Input.h"

#include "imgui/imgui.h"

namespace sre
{

void SceneViewportCamera::onInit()
{
	this->camera = SPTR<Entity>(new Entity{ "_editor_camera" });
	this->cameraComponent = this->camera->addComponent<CameraComponent>();
	this->cameraComponent->setPerspectiveProjection(70.0f, EngineValues::ASPECT_RATIO, 0.1f, 1000.0f);

	this->flyingComponent = this->camera->addComponent<FlyingMovementComponent>();
	this->orbitComponent = this->camera->addComponent<OrbitMovementComponent>();

	this->camera->getTransform()->setPosition({ 0.0f, 2.0f, 5.0f });
	this->camera->onInit();

	this->viewingState = EViewingState::NONE;

	this->multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
}

void SceneViewportCamera::onUpdate(float elapsedTime)
{
	this->updateViewingState();
	this->processMouseWheel(elapsedTime);

	if (this->viewingState != EViewingState::NONE)
	{
		this->processCameraMovement(elapsedTime);
		this->forceInitialMousePosition();
	}

	this->camera->onUpdate(elapsedTime);
}
 
void SceneViewportCamera::updateCameraPerspective(float newWidth, float newHeight)
{
	if ((newWidth != this->currentWindowWidth) || (newHeight != this->currentWindowHeight))
	{
		this->currentWindowWidth = newWidth;
		this->currentWindowHeight = newHeight;
		float aspectRatio = this->currentWindowWidth / this->currentWindowHeight;
		this->camera->getComponent<CameraComponent>()->setPerspectiveProjection(70.0f, aspectRatio, 0.1f, 1000.0f);
	}
}

void SceneViewportCamera::getCameraMatrices(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	viewMatrix = this->cameraComponent->getViewMatrix();
	projectionMatrix = this->cameraComponent->getProjectionMatrix();
}

void SceneViewportCamera::updateViewingState()
{
	if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
	{
		if (this->viewingState != EViewingState::FLYING)
		{
			this->viewingState = EViewingState::FLYING;
			this->multimediaManager->showMouseCursor(false);
			this->updateInitialMousePosition();
		}
	}
	else if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsKeyDown(ImGuiKey_LeftAlt))
	{
		if (this->viewingState != EViewingState::ORBIT)
		{
			this->viewingState = EViewingState::ORBIT;
			this->multimediaManager->showMouseCursor(false);
			this->updateInitialMousePosition();
		}
	}
	else if (this->viewingState != EViewingState::NONE)
	{
		this->viewingState = EViewingState::NONE;
		this->multimediaManager->showMouseCursor(true);

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = io.ConfigFlags & ~ImGuiConfigFlags_NoMouseCursorChange;
	}
}

void SceneViewportCamera::processCameraMovement(float elapsedTime)
{
	const glm::ivec2& mouseDelta = Input::getMouseDeltaPosition();

	if (this->viewingState == EViewingState::FLYING)
	{
		TransformComponent* transform = this->camera->getTransform();

		glm::vec3 moveDirection{ 0.0f };

		if (Input::isKeyDown(KEY_a))
			moveDirection -= transform->getRight();
		if (Input::isKeyDown(KEY_d))
			moveDirection += transform->getRight();
		if (Input::isKeyDown(KEY_w))
			moveDirection -= transform->getForward();
		if (Input::isKeyDown(KEY_s))
			moveDirection += transform->getForward();

		this->flyingComponent->processMovement(moveDirection, mouseDelta, elapsedTime);
	}
	else
	{
		this->orbitComponent->move(mouseDelta, elapsedTime);
	}
}

void SceneViewportCamera::processMouseWheel(float elapsedTime)
{
	int mouseWheel = Input::getMouseWheel();
	if (mouseWheel != 0)
	{
		if (this->viewingState == EViewingState::FLYING)
		{
			this->flyingComponent->addSpeed(static_cast<float>(mouseWheel), elapsedTime);
		}
		else
		{
			const float WHEEL_RATE = 100.0f;
			glm::vec3 position = this->camera->getTransform()->getPosition();
			glm::vec3 targetPosition = TransformComponent::ZERO;
			float targetDistance = glm::distance(position, targetPosition);
			targetDistance = targetDistance - (mouseWheel * WHEEL_RATE * elapsedTime);
			targetDistance = (targetDistance < 1.0f) ? 1.0f : targetDistance;

			position = glm::normalize(position);
			position = position * targetDistance;

			this->camera->getTransform()->setPosition(position);
		}
	}
}

void SceneViewportCamera::updateInitialMousePosition()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	this->initialMousePosition = Input::getMousePixelCoordPosition();
}

void SceneViewportCamera::forceInitialMousePosition()
{
	this->multimediaManager->setMousePosition(this->initialMousePosition.x, this->initialMousePosition.y);
}

} // namespace
