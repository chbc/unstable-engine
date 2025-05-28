#include "EditorSceneViewport.h"
#include "SingletonsManager.h"
#include "TextureCreator.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "EngineValues.h"
#include "RenderManager.h"
#include "ScenesManager.h"
#include "FlyingCameraComponent.h"
#include "OrbitCameraComponent.h"
#include "Input.h"
#include "EditorsController.h"

#include "imgui/imgui.h"

#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

uint32_t EditorSceneViewport::Fbo = 0;

EditorSceneViewport::EditorSceneViewport(EditorsController* arg_controller) : controller(arg_controller)
{ }

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
		this->textureId = reinterpret_cast<void*>(id);

		this->renderManager = singletonsManager->get<RenderManager>();

		this->camera = SPTR<Entity>(new Entity{"_editor_camera"});
		this->flyingComponent = this->camera->addComponent<FlyingCameraComponent>();
		this->flyingComponent->setPerspectiveProjection(70.0f, EngineValues::ASPECT_RATIO, 0.1f, 1000.0f);

		this->orbitComponent = this->camera->addComponent<OrbitCameraComponent>();
		this->orbitComponent->setPerspectiveProjection(70.0f, EngineValues::ASPECT_RATIO, 0.1f, 1000.0f);
		this->orbitComponent->setEnabled(false);
		
		this->camera->getTransform()->setPosition({ 0.0f, 2.0f, 5.0f });

		this->camera->onInit();

		this->renderManager->setEditorCamera(flyingComponent);
	}

	this->renderManager->setTargetFBO(Fbo);
	this->canUpdate = false;
}

void EditorSceneViewport::onUpdate(float elapsedTime)
{
	if (this->canUpdate)
	{
		this->updateViewingState();
		this->processMouseWheel(elapsedTime);
		this->camera->onUpdate(elapsedTime);

		if (this->flyingComponent->isEnabled() || this->orbitComponent->isEnabled())
		{
			this->forceInitialMousePosition();
		}
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

	this->canUpdate = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();

	this->handleFileDrop();
	this->updateCameraPerspective(size.x, size.y);

	ImGui::End();
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
		if (!this->flyingComponent->isEnabled())
		{
			this->orbitComponent->setEnabled(false);
			this->flyingComponent->setEnabled(true);
			this->renderManager->setEditorCamera(flyingComponent);
			this->multimediaManager->showMouseCursor(false);
			this->updateInitialMousePosition();
		}
	}
	else if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftAlt)))
	{
		if (!this->orbitComponent->isEnabled())
		{
			this->flyingComponent->setEnabled(false);
			this->orbitComponent->setEnabled(true);
			this->renderManager->setEditorCamera(orbitComponent);
			this->multimediaManager->showMouseCursor(false);
			this->updateInitialMousePosition();
		}
	}
	else if (this->flyingComponent->isEnabled() || this->orbitComponent->isEnabled())
	{
		this->flyingComponent->setEnabled(false);
		this->orbitComponent->setEnabled(false);
		this->multimediaManager->showMouseCursor(true);

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = io.ConfigFlags & ~ImGuiConfigFlags_NoMouseCursorChange;
	}
}

void EditorSceneViewport::processMouseWheel(float elapsedTime)
{
	if (!this->flyingComponent->isEnabled())
	{
		int mouseWheel = Input::getMouseWheel();

		if (mouseWheel != 0)
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

void EditorSceneViewport::updateInitialMousePosition()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	this->initialMousePosition = Input::getMousePosition();
}

void EditorSceneViewport::forceInitialMousePosition()
{
	this->multimediaManager->setMousePosition(this->initialMousePosition.x, this->initialMousePosition.y);
}

void EditorSceneViewport::updateCameraPerspective(float newWidth, float newHeight)
{
	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) &&
		(
			(newWidth != this->currentWindowWidth) ||
			(newHeight != this->currentWindowHeight)
		)
	)
	{
		this->currentWindowWidth = newWidth;
		this->currentWindowHeight = newHeight;
		float aspectRatio = this->currentWindowWidth / this->currentWindowHeight;
		this->flyingComponent->setPerspectiveProjection(70.0f, aspectRatio, 0.1f, 1000.0f);
		this->orbitComponent->setPerspectiveProjection(70.0f, aspectRatio, 0.1f, 1000.0f);
	}
}

} // namespace
