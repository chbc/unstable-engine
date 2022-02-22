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
	class FlyingCameraComponent* flyingCamera;
	class OrbitCameraComponent* orbitCamera;

	static uint32_t Fbo;
	void* textureId;
	bool canUpdate;

public:
	EditorSceneViewport(SceneManager* arg_sceneManager);

	void onInit() override;
	void onUpdate(uint32_t elapsedTime) override;
	void onEditorGUI() override;
	void onRelease() override;

private:
	void processInput();
	void updateViewingState();
	void processMouseWheel();

friend class WorldEditor;
};

} // namespace
