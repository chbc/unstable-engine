#include "EditorSceneViewport.h"
#include "SingletonsManager.h"
#include "TextureCreator.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "EngineValues.h"
#include "RenderManager.h"
#include "ScenesManager.h"
#include "FlyingMovementComponent.h"
#include "OrbitMovementComponent.h"
#include "Input.h"
#include "EditorsController.h"
#include "MessagesManager.h"
#include "MathUtils.h"

#include "imgui.h"
#include "imguizmo/ImGuizmo.h"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

uint32_t EditorSceneViewport::Fbo = 0;

EditorSceneViewport::EditorSceneViewport(EditorsController* arg_controller) : controller(arg_controller)
{
	Action* action = new Action{ [&](void* message) { this->onEntitySelected(message); } };
	this->selectionAction = SPTR<Action>(action);
}

void EditorSceneViewport::onInit()
{
	if (this->renderManager == nullptr)
	{
		SingletonsManager* singletonsManager = SingletonsManager::getInstance();

		this->multimediaManager = singletonsManager->get<MultimediaManager>();
		uint32_t width = static_cast<uint32_t>(EngineValues::SCREEN_WIDTH);
		uint32_t height = static_cast<uint32_t>(EngineValues::SCREEN_HEIGHT);

		TextureCreator* textureCreator = singletonsManager->get<TextureCreator>();
		Texture* texture = textureCreator->createEmptyTexture(width, height);
		uint32_t id = texture->getId();

		AGraphicsWrapper* graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
		Fbo = graphicsWrapper->generateColorFrameBuffer(
			std::vector<uint32_t>{id}, texture->getWidth(), texture->getHeight()
		);
		this->textureId = static_cast<uint64_t>(id);

		this->renderManager = singletonsManager->get<RenderManager>();

		this->camera = SPTR<Entity>(new Entity{"_editor_camera"});
		this->cameraComponent = this->camera->addComponent<CameraComponent>();
		this->cameraComponent->setPerspectiveProjection(70.0f, EngineValues::ASPECT_RATIO, 0.1f, 1000.0f);
		
		this->flyingComponent = this->camera->addComponent<FlyingMovementComponent>();
		this->orbitComponent = this->camera->addComponent<OrbitMovementComponent>();
		
		this->camera->getTransform()->setPosition({ 0.0f, 2.0f, 5.0f });

		this->camera->onInit();

		this->renderManager->setEditorCamera(this->cameraComponent);
		this->viewingState = EViewingState::NONE;
	}

	this->renderManager->setTargetFBO(Fbo);
	this->canUpdate = false;

	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<EntitySelectionMessage>(this->selectionAction.get());
	this->selectedEntity = nullptr;
	this->guizmoOperation = ImGuizmo::TRANSLATE;
}

void EditorSceneViewport::onUpdate(float elapsedTime)
{
	if (this->canUpdate)
	{
		this->updateViewingState();
		this->processMouseWheel(elapsedTime);
		this->processGuizmoOperationSelection();

		if (this->viewingState != EViewingState::NONE)
		{
			this->processCameraMovement(elapsedTime);
			this->forceInitialMousePosition();
		}

		this->camera->onUpdate(elapsedTime);
	}
}

void EditorSceneViewport::onEditorGUI()
{
	ImGui::Begin("Viewport");
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;
	style.WindowPadding = ImVec2{ 0.0f, 0.0f };
	ImVec2 size = ImGui::GetContentRegionAvail();

	ImGui::Image(this->textureId, size, ImVec2{0.0f, 1.0f}, ImVec2{ 1.0f, 0.0f });

	this->canUpdate = ImGui::IsWindowHovered();

	this->handleFileDrop();
	this->updateCameraPerspective(size.x, size.y);


	// GUIZMO
	if (this->selectedEntity != nullptr)
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();

		ImVec2 windowPosition = ImGui::GetWindowPos();
		ImGuizmo::SetRect(windowPosition.x, windowPosition.y, size.x, size.y);

		const glm::mat4& viewMatrix = this->cameraComponent->getViewMatrix();
		const glm::mat4& projectionMatrix = this->cameraComponent->getProjectionMatrix();
		TransformComponent* entityTransform = this->selectedEntity->getTransform();
		glm::mat4 entityMatrix = entityTransform->getMatrix();
		
		if (this->viewingState == EViewingState::NONE)
		{
			ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
				this->guizmoOperation, ImGuizmo::LOCAL, glm::value_ptr(entityMatrix));

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 position{ 0.0f }, scale{ 0.0f }, rotation{ 0.0f };
				MathUtils::decomposeTransform(entityMatrix, position, scale, rotation);

				entityTransform->setPosition(position);
				entityTransform->setScale(scale);
				entityTransform->setRotation(glm::degrees(rotation));
			}
		}
	}

	ImGui::End();
}

void EditorSceneViewport::onCleanUp()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->removeListener<EntitySelectionMessage>(this->selectionAction.get());
}

void EditorSceneViewport::onRelease()
{
	if (Fbo != 0)
	{
		AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
		graphicsWrapper->deleteFrameBuffer(Fbo);
	}
}

void EditorSceneViewport::handleFileDrop()
{
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE"))
		{
			const char* filePath = static_cast<const char*>(payload->Data);
			if (filePath != nullptr)
			{
				this->controller->loadFileFromBrowser(filePath);
			}
		}
		ImGui::EndDragDropTarget();
	}
}

void EditorSceneViewport::updateViewingState()
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

void EditorSceneViewport::processCameraMovement(float elapsedTime)
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

void EditorSceneViewport::processMouseWheel(float elapsedTime)
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

void EditorSceneViewport::processGuizmoOperationSelection()
{
	if (this->viewingState == EViewingState::NONE)
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
}

void EditorSceneViewport::updateInitialMousePosition()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	this->initialMousePosition = Input::getMousePixelCoordPosition();
}

void EditorSceneViewport::forceInitialMousePosition()
{
	this->multimediaManager->setMousePosition(this->initialMousePosition.x, this->initialMousePosition.y);
}

void EditorSceneViewport::updateCameraPerspective(float newWidth, float newHeight)
{
	if((newWidth != this->currentWindowWidth) || (newHeight != this->currentWindowHeight))
	{
		this->currentWindowWidth = newWidth;
		this->currentWindowHeight = newHeight;
		float aspectRatio = this->currentWindowWidth / this->currentWindowHeight;
		this->camera->getComponent<CameraComponent>()->setPerspectiveProjection(70.0f, aspectRatio, 0.1f, 1000.0f);
	}
}

void EditorSceneViewport::onEntitySelected(void* data)
{
	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);
	this->selectedEntity = message->entity;
}

} // namespace
