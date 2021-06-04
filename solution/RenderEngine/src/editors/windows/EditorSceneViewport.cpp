#include "EditorSceneViewport.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "EngineValues.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"

#include "imgui/imgui.h"
#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

uint32_t EditorSceneViewport::Fbo = 0;

EditorSceneViewport::EditorSceneViewport(SceneManager* arg_sceneManager) 
	: sceneManager(arg_sceneManager), renderManager(nullptr), 
	cameraEntity(nullptr), camera(nullptr), textureId(nullptr)
{ }

void EditorSceneViewport::onInit()
{
	if (this->renderManager == nullptr)
	{
		SingletonsManager* singletonsManager = SingletonsManager::getInstance();

		MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
		uint32_t width = static_cast<uint32_t>(EngineValues::SCREEN_WIDTH);
		uint32_t height = static_cast<uint32_t>(EngineValues::SCREEN_HEIGHT);

		TextureManager* textureManager = singletonsManager->resolve<TextureManager>();
		Texture* texture = textureManager->createEmptyTexture(width, height);
		uint32_t id = texture->getId();

		AGraphicsWrapper* graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
		Fbo = graphicsWrapper->generateColorFrameBuffer(
			std::vector<uint32_t>{id}, texture->getWidth(), texture->getHeight()
		);
		this->textureId = reinterpret_cast<void*>(id);

		this->renderManager = SingletonsManager::getInstance()->get<RenderManager>();

		this->cameraEntity = UPTR<Entity>(new Entity{});
		camera = cameraEntity->addComponent<CameraComponent>();
		camera->setPerspectiveProjection(100.0, EngineValues::SCREEN_WIDTH / EngineValues::SCREEN_HEIGHT, 0.1f, 1000.0f);
		
		glm::vec3 position{ 0.0f, 2.5f, 10.0f };
		this->camera->setPosition(position);
		this->cameraDistance = glm::distance(position, glm::vec3(0, 0, 0));
	}

	this->renderManager->setTargetFBO(Fbo);
	this->renderManager->setMainCamera(this->cameraEntity->getComponent<CameraComponent>());
	this->isViewingActive = false;
}

void EditorSceneViewport::onEditorGUI()
{
	ImGui::Begin("Viewport");
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;
	style.WindowPadding = ImVec2{ 0.0f, 0.0f };
	ImVec2 size = ImGui::GetContentRegionAvail();

	ImGui::Image(this->textureId, size, ImVec2{0.0f, 1.0f}, ImVec2{ 1.0f, 0.0f });

	if (ImGui::IsWindowFocused())
		this->processInput();

	ImGui::End();
}

void EditorSceneViewport::onRelease()
{
	this->renderManager->setTargetFBO(0);
}

void EditorSceneViewport::processInput()
{
	const ImGuiIO& io = ImGui::GetIO();

	this->updateViewingState();
	this->processMouseMotion(io);
	this->processMouseWheel(io);
	this->processMouseButtons();
}

void EditorSceneViewport::updateViewingState()
{
	this->isViewingActive = ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Space));
}

void EditorSceneViewport::processMouseMotion(const ImGuiIO& io)
{
	if
	(
		this->isViewingActive &&
		((io.MouseDelta.x != 0.0f) || (io.MouseDelta.y != 0.0f))
	)
	{
		const float SPEED = 0.02f;
		glm::vec3 position = this->camera->getPosition();

		glm::vec3 direction = glm::normalize(position - glm::vec3{ 0.0f });
		glm::vec3 right = glm::cross(direction, glm::vec3{ 0.0f, 1.0f, 0.0f });
		glm::vec3 axis = glm::normalize((right * io.MouseDelta.y) + (glm::vec3{ 0.0f, 1.0f, 0.0f } *(-io.MouseDelta.x)));
		float angle = glm::vec2{ io.MouseDelta.x, io.MouseDelta.y }.length() * SPEED;

		direction = glm::rotate(direction, angle, axis);
		position = direction * this->cameraDistance;

		this->camera->setPosition(position);
	}
}

void EditorSceneViewport::processMouseWheel(const ImGuiIO& io)
{
	if (io.MouseWheel != 0.0f)
	{
		this->cameraDistance -= io.MouseWheel;

		glm::vec3 position = this->camera->getPosition();
		position = glm::normalize(position);
		position *= this->cameraDistance;

		this->camera->setPosition(position);
	}
}

void EditorSceneViewport::processMouseButtons()
{
	static float yLookAt = 0.0f;

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Middle))
	{
		yLookAt += 1.0f;
		this->camera->setLookAt(glm::vec3(0.0f, yLookAt, 0.0f));
	}
}

} // namespace
