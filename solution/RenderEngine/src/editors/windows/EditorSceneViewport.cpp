#include "EditorSceneViewport.h"
#include "SingletonsManager.h"
#include "TextureManager.h"
#include "AGraphicsWrapper.h"
#include "MultimediaManager.h"
#include "EngineValues.h"
#include "RenderManager.h"

#include "imgui/imgui.h"

namespace sre
{

uint32_t EditorSceneViewport::Fbo = 0;

EditorSceneViewport::EditorSceneViewport() : renderManager(nullptr), textureId(nullptr)
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
	}

	this->renderManager->setTargetFBO(Fbo);
}

void EditorSceneViewport::onEditorGUI()
{
	ImGui::Begin("Viewport");
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 0.0f;
	style.WindowPadding = ImVec2{ 0.0f, 0.0f };
	ImVec2 size = ImGui::GetContentRegionAvail();

	ImGui::Image(this->textureId, size, ImVec2{0.0f, 1.0f}, ImVec2{ 1.0f, 0.0f });
	ImGui::End();
}

void EditorSceneViewport::onRelease()
{
	this->renderManager->setTargetFBO(0);
}

} // namespace
