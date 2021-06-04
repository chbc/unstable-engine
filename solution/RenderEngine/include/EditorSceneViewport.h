#pragma once

#include "IEditorWindow.h"
#include "Texture.h"
#include "memory_aliases.h"

struct ImGuiIO;

namespace sre
{

class SceneManager;

class EditorSceneViewport : public IEditorWindow
{
private:
	SceneManager* sceneManager;
	class RenderManager* renderManager;
	SPTR<class Entity> cameraEntity;
	class CameraComponent* camera;

	static uint32_t Fbo;
	void* textureId;
	float cameraDistance;
	bool isViewingActive;

public:
	EditorSceneViewport(SceneManager* arg_sceneManager);

	void onInit() override;
	void onEditorGUI() override;
	void onRelease() override;

private:
	void processInput();
	void updateViewingState();
	void processMouseMotion(const ImGuiIO& io);
	void processMouseWheel(const ImGuiIO& io);
	void processMouseButtons();

friend class WorldEditor;
};

} // namespace
