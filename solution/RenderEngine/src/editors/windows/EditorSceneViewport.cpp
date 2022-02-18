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
#include "FlyingCameraComponent.h"
#include "OrbitCameraComponent.h"

#include "imgui/imgui.h"
#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

uint32_t EditorSceneViewport::Fbo = 0;

EditorSceneViewport::EditorSceneViewport(SceneManager* arg_sceneManager) 
	: sceneManager(arg_sceneManager), renderManager(nullptr), 
	cameraEntity(nullptr), textureId(nullptr)
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
		this->flyingCamera = cameraEntity->addComponent<FlyingCameraComponent>();
		this->flyingCamera->setPerspectiveProjection(100.0, EngineValues::SCREEN_WIDTH / EngineValues::SCREEN_HEIGHT, 0.1f, 1000.0f);

		this->orbitCamera = cameraEntity->addComponent<OrbitCameraComponent>();
		this->orbitCamera->setPerspectiveProjection(100.0, EngineValues::SCREEN_WIDTH / EngineValues::SCREEN_HEIGHT, 0.1f, 1000.0f);
		
		glm::vec3 position{ 0.0f, 2.5f, 10.0f };
		this->cameraEntity->getTransform()->setPosition(position);
		this->cameraDistance = glm::distance(position, glm::vec3(0, 0, 0));

		this->cameraEntity->onStart();
		this->orbitCamera->setEnabled(false);
	}

	this->renderManager->setTargetFBO(Fbo);
	this->renderManager->setMainCamera(this->flyingCamera);
	this->isFocused = false;
}

void EditorSceneViewport::onUpdate(uint32_t elapsedTime)
{
	if (this->isFocused)
		this->cameraEntity->onUpdate(elapsedTime);
}

void EditorSceneViewport::onEditorGUI()
{
	ImGui::Begin("Viewport");
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;
	style.WindowPadding = ImVec2{ 0.0f, 0.0f };
	ImVec2 size = ImGui::GetContentRegionAvail();

	ImGui::Image(this->textureId, size, ImVec2{0.0f, 1.0f}, ImVec2{ 1.0f, 0.0f });

	this->isFocused = ImGui::IsWindowFocused();
	if (this->isFocused)
		this->processInput();

	ImGui::End();
}

void EditorSceneViewport::onRelease()
{
	this->renderManager->setTargetFBO(0);
}

void EditorSceneViewport::processInput()
{
	this->updateViewingState();
}

void EditorSceneViewport::updateViewingState()
{
	if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Space)))
	{
		if (!this->orbitCamera->isEnabled())
		{
			this->orbitCamera->setEnabled(true);
			this->flyingCamera->setEnabled(false);
			this->orbitCamera->setLookAt(this->flyingCamera->getLookAt());
			this->renderManager->setMainCamera(this->orbitCamera);
		}
	}
	else if (!this->flyingCamera->isEnabled())
	{
		this->orbitCamera->setEnabled(false);
		this->flyingCamera->setEnabled(true);
		this->flyingCamera->setLookAt(this->orbitCamera->getLookAt());
		this->renderManager->setMainCamera(this->flyingCamera);
	}
}

} // namespace
