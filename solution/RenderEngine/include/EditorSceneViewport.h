#pragma once

#include "IEditorWindow.h"
#include "Texture.h"
#include "SceneViewportCamera.h"
#include "SceneViewportGuizmos.h"
#include "SceneViewportButtons.h"
#include "EditorMessages.h"

namespace sre
{

class EditorsController;

class EditorSceneViewport : public IEditorWindow
{
private:
	SceneViewportCamera sceneViewportCamera;
	SceneViewportGuizmos sceneViewportGuizmos;
	SceneViewportButtons sceneViewportButtons;
	SPTR<Action> gridEnabledAction;
	class RenderManager* renderManager{ nullptr };
	class MultimediaManager* multimediaManager{ nullptr };
	EditorsController* controller{ nullptr };
	Entity* gridEntity{ nullptr };
	static uint32_t Fbo;
	uint64_t textureId{ 0 };
	bool isWindowHovered{ false };

public:
	EditorSceneViewport(EditorsController* arg_controller);

	void onInit() override;
	void onUpdate(float elapsedTime) override;
	void onEditorGUI() override;
	void onCleanUp() override;
	void onRelease() override;

private:
	void handleFileDrop();
	void handleFocusInput();
	void tryPickEntity(const glm::vec2& viewportSize, const glm::vec2& windowPosition);
	void onSetGridEnabled(void* message);

friend class WorldEditor;
};

} // namespace
