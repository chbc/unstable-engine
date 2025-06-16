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

	this->isWindowHovered = ImGui::IsWindowHovered();

	this->handleFileDrop();
	this->sceneViewportCamera.updateCameraPerspective(size.x, size.y);

	if (!this->sceneViewportCamera.isCameraMoving())
	{
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		this->sceneViewportCamera.getCameraMatrices(viewMatrix, projectionMatrix);

		bool entityManipulated = this->sceneViewportGuizmos.drawAndManipulate(size.x, size.y, viewMatrix, projectionMatrix);
		if (this->isWindowHovered && !entityManipulated)
		{
			tryPickEntity(size.x, size.y);
		}
	}

	ImGui::End();
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

void EditorSceneViewport::tryPickEntity(float viewportWidth, float viewportHeight)
{
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		ImVec2 mousePosition = ImGui::GetMousePos();
		glm::vec2 viewportSize{ viewportWidth, viewportHeight };
		
		ScenesManager* scenesManager = SingletonsManager::getInstance()->get<ScenesManager>();
		Entity* pickedEntity = scenesManager->raycastFromScreen({ mousePosition.x, mousePosition.y }, viewportSize);
		this->controller->notifyEntitySelection(pickedEntity);

		if (pickedEntity != nullptr)
		{
			Bounds bounds;
			pickedEntity->getBounds(bounds);

			this->renderManager->addDebugBox(
				pickedEntity->getTransform()->getPosition() + bounds.center,
				bounds.size,
				glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f }
			);
		}
	}
}

} // namespace
