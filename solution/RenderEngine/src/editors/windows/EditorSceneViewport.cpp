#include "EditorSceneViewport.h"
#include "SingletonsManager.h"
#include "TextureCreator.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "EngineValues.h"
#include "RenderManager.h"
#include "ScenesManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "FlyingCameraComponent.h"
#include "OrbitCameraComponent.h"
#include "Input.h"

#include "imgui/imgui.h"
#include "glm/vec2.hpp"
#include <glm/gtx/rotate_vector.hpp>

namespace sre
{

uint32_t EditorSceneViewport::Fbo = 0;

EditorSceneViewport::EditorSceneViewport(ScenesManager* arg_scenesManager) 
	: scenesManager(arg_scenesManager), renderManager(nullptr), textureId(nullptr),
	canUpdate(false), flyingCamera(nullptr), orbitCamera(nullptr), currentCamera(nullptr)
{ }

void EditorSceneViewport::onInit()
{
	if (this->renderManager == nullptr)
	{
		SingletonsManager* singletonsManager = SingletonsManager::getInstance();

		MultimediaManager* multimediaManager = singletonsManager->get<MultimediaManager>();
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

		this->renderManager = SingletonsManager::getInstance()->get<RenderManager>();

		this->flyingCamera = UPTR<Entity>(new Entity{"_editor_flying_camera"});
		CameraComponent* flyingComponent = this->flyingCamera->addComponent<FlyingCameraComponent>();
		flyingComponent->setPerspectiveProjection(70.0f, EngineValues::ASPECT_RATIO, 0.1f, 1000.0f);

		this->orbitCamera = SPTR<Entity>(new Entity{ "_editor_orbit_camera" });
		CameraComponent* orbitComponent = this->orbitCamera->addComponent<OrbitCameraComponent>();
		orbitComponent->setPerspectiveProjection(70.0f, EngineValues::ASPECT_RATIO, 0.1f, 1000.0f);
		
		this->flyingCamera->getTransform()->setPosition({ 0.0f, 5.0f, -10.0f });

		this->flyingCamera->onInit();
		this->orbitCamera->onInit();
		this->currentCamera = this->flyingCamera.get();

		this->orbitCamera->setEnabled(false);
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
		this->processMouseWheel();
		this->currentCamera->onUpdate(elapsedTime);
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

void EditorSceneViewport::updateViewingState()
{
	/*
	if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftAlt)))
	{
		if (!this->orbitCamera->isEnabled())
		{
			glm::vec3 lookAt = this->flyingCamera->getLookAt();
			this->orbitCamera->setLookAt(lookAt);
			this->flyingCamera->setEnabled(false);
			this->orbitCamera->setEnabled(true);
			this->renderManager->setEditorCamera(this->orbitCamera);
		}
	}
	else if (!this->flyingCamera->isEnabled())
	{
		glm::vec3 lookAt = this->orbitCamera->getLookAt();
		this->flyingCamera->setLookAt(lookAt);
		this->orbitCamera->setEnabled(false);
		this->flyingCamera->setEnabled(true);
		this->renderManager->setEditorCamera(this->flyingCamera);
	}
	*/
}

void EditorSceneViewport::processMouseWheel()
{
	/*
	int mouseWheel = Input::getMouseWheel();

	if (mouseWheel != 0)
	{
		const float SPEED = 3.0f;
		glm::vec3 position = this->cameraEntity->getTransform()->getPosition();
		glm::vec3 targetPosition = this->flyingCamera->getLookAt();
		float targetDistance = glm::distance(position, targetPosition);
		targetDistance = targetDistance - (mouseWheel * SPEED);
		targetDistance = (targetDistance < 1.0f) ? 1.0f : targetDistance;

		position = glm::normalize(position);
		position = position * targetDistance;

		this->cameraEntity->getTransform()->setPosition(position);
	}
	*/
}

} // namespace
