#include "SceneViewportCamera.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "FlyingMovementComponent.h"
#include "OrbitMovementComponent.h"
#include "PanMovementComponent.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "EngineValues.h"
#include "Input.h"
#include "ScenesManager.h"

#include "imgui/imgui.h"

namespace sre
{

void SceneViewportCamera::onInit()
{
	ScenesManager* scenesManager = SingletonsManager::getInstance()->get<ScenesManager>();
	Scene* editorScene = scenesManager->getEditorScene();

	Entity* camera = editorScene->createPerspectiveCamera();
	this->flyingComponent = camera->addComponent<FlyingMovementComponent>();
	this->orbitComponent = camera->addComponent<OrbitMovementComponent>();
	this->panComponent = camera->addComponent<PanMovementComponent>();
	this->cameraComponent = camera->getComponent<CameraComponent>();
	this->cameraTransform = camera->getTransform();
	this->cameraTransform->setPosition({ 0.0f, 2.0f, 5.0f }); 

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
}
 
void SceneViewportCamera::updateCameraPerspective(float newWidth, float newHeight)
{
	if ((newWidth != this->currentWindowWidth) || (newHeight != this->currentWindowHeight))
	{
		this->currentWindowWidth = newWidth;
		this->currentWindowHeight = newHeight;
		float aspectRatio = this->currentWindowWidth / this->currentWindowHeight;
		this->cameraComponent->setPerspectiveProjection(70.0f, aspectRatio, 0.01f, 1000.0f);
	}
}

void SceneViewportCamera::getCameraMatrices(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	viewMatrix = this->cameraComponent->getViewMatrix();
	projectionMatrix = this->cameraComponent->getProjectionMatrix();
}

void SceneViewportCamera::setCameraFocus(const glm::vec3& newTarget)
{
	this->orbitComponent->setTarget(newTarget);
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
	else if	(ImGui::IsKeyDown(ImGuiKey_LeftAlt) && (ImGui::IsMouseDown(ImGuiMouseButton_Left)))
	{
		if (this->viewingState != EViewingState::ORBIT)
		{
			this->viewingState = EViewingState::ORBIT;
			this->multimediaManager->showMouseCursor(false);
			this->updateInitialMousePosition();
			this->orbitComponent->updateTarget();
		}
	}
	else if (ImGui::IsMouseDown(ImGuiMouseButton_Middle))
	{
		if (this->viewingState != EViewingState::PAN)
		{
			this->viewingState = EViewingState::PAN;
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

	switch (this->viewingState)
	{
		case EViewingState::FLYING:
		{
			glm::vec3 moveDirection{ 0.0f };

			if (Input::isKeyDown(KEY_a))
				moveDirection -= this->cameraTransform->getRight();
			if (Input::isKeyDown(KEY_d))
				moveDirection += this->cameraTransform->getRight();
			if (Input::isKeyDown(KEY_w))
				moveDirection -= this->cameraTransform->getForward();
			if (Input::isKeyDown(KEY_s))
				moveDirection += this->cameraTransform->getForward();

			this->flyingComponent->processMovement(moveDirection, mouseDelta, elapsedTime);
			break;
		}
		case EViewingState::ORBIT:
			this->orbitComponent->move(mouseDelta, elapsedTime);
			break;
		case EViewingState::PAN:
			this->panComponent->move(mouseDelta, elapsedTime);
			break;
		default: break;
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
			glm::vec3 position = this->cameraTransform->getPosition();
			position -= this->cameraTransform->getForward() * (static_cast<float>(mouseWheel) * WHEEL_RATE * elapsedTime);
			this->cameraTransform->setPosition(position);
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
