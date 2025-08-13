#include "EditorSceneViewport.h"
#include "SingletonsManager.h"
#include "TextureCreator.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "EngineValues.h"
#include "RenderManager.h"
#include "ScenesManager.h"
#include "EditorsController.h"

#include <imgui/imgui.h>

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
		this->textureId = static_cast<uint64_t>(id);

		this->sceneViewportCamera.onInit();

		this->renderManager = singletonsManager->get<RenderManager>();
		this->renderManager->setEditorCamera(this->sceneViewportCamera.getCameraComponent());
	}

	this->renderManager->setTargetFBO(Fbo);
	this->isWindowHovered = false;

	this->sceneViewportGuizmos.onInit();
}

void EditorSceneViewport::onUpdate(float elapsedTime)
{
	if (this->isWindowHovered)
	{
		this->sceneViewportCamera.onUpdate(elapsedTime);
		if (!this->sceneViewportCamera.isCameraMoving())
		{
			this->sceneViewportGuizmos.processGuizmoOperationSelection();
		}
		this->handleFocusInput();
	}
}

void EditorSceneViewport::onEditorGUI()
{
	ImGui::Begin("Viewport");
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;
	style.WindowPadding = ImVec2{ 0.0f, 0.0f };

	ImVec2 position = ImGui::GetCursorScreenPos();
	ImVec2 size = ImGui::GetContentRegionAvail();

	glm::vec2 windowPosition{ position.x, position.y };
	glm::vec2 windowSize{ size.x, size.y };

	ImGui::Image(this->textureId, size, ImVec2{0.0f, 1.0f}, ImVec2{ 1.0f, 0.0f });

	this->isWindowHovered = ImGui::IsWindowHovered();

	this->handleFileDrop();
	this->sceneViewportCamera.updateCameraPerspective(size.x, size.y);

	bool cameraMoving = this->sceneViewportCamera.isCameraMoving();

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	this->sceneViewportCamera.getCameraMatrices(viewMatrix, projectionMatrix);

	bool entityManipulated = this->sceneViewportGuizmos.drawAndManipulate
	(
		cameraMoving, windowPosition, windowSize, viewMatrix, projectionMatrix
	);

	if (!cameraMoving && this->isWindowHovered && !entityManipulated)
	{
		tryPickEntity(windowSize, windowPosition);
	}

	ImGui::End();

	this->sceneViewportButtons.drawContent(windowPosition, windowSize);
}

void EditorSceneViewport::onCleanUp()
{
	this->sceneViewportGuizmos.onCleanUp();
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

void EditorSceneViewport::handleFocusInput()
{
	if (ImGui::IsKeyPressed(ImGuiKey_F))
	{
		Entity* selectedEntity = this->controller->getSelectedEntity();
		if (selectedEntity != nullptr)
		{
			glm::vec3 position = selectedEntity->getTransform()->getPosition();
			this->sceneViewportCamera.setCameraFocus(position);
		}
	}
}

void EditorSceneViewport::tryPickEntity(const glm::vec2& viewportSize, const glm::vec2& windowPosition)
{
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		ImVec2 mousePosition = ImGui::GetMousePos();
		glm::vec2 resultMousePosition{ mousePosition.x - windowPosition.x, mousePosition.y - windowPosition.y };
		
		ScenesManager* scenesManager = SingletonsManager::getInstance()->get<ScenesManager>();
		Entity* currentEntity = this->controller->getSelectedEntity();
		Entity* pickedEntity = scenesManager->raycastFromScreen(resultMousePosition, viewportSize, currentEntity);
		this->controller->setSelectedEntity(pickedEntity);
	}
}

} // namespace
