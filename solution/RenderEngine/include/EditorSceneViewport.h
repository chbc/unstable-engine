#pragma once

#include "IEditorWindow.h"
#include "Texture.h"
#include "memory_aliases.h"

struct ImGuiIO;

namespace sre
{

class ScenesManager;

class EditorSceneViewport : public IEditorWindow
{
private:
	ScenesManager* scenesManager{ nullptr };
	class RenderManager* renderManager{ nullptr };
	SPTR<class Entity> camera{ nullptr };
	class FlyingCameraComponent* flyingComponent;
	class OrbitCameraComponent* orbitComponent;

	static uint32_t Fbo;
	void* textureId{ nullptr };
	bool canUpdate{ false };

public:
	EditorSceneViewport(ScenesManager* arg_scenesManager);

	void onInit() override;
	void onUpdate(float elapsedTime) override;
	void onEditorGUI() override;
	void onRelease() override;

private:
	void updateViewingState();
	void processMouseWheel();

friend class WorldEditor;
};

} // namespace
