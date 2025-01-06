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
	ScenesManager* scenesManager;
	class RenderManager* renderManager;
	SPTR<class Entity> flyingCamera;
	SPTR<class Entity> orbitCamera;
	Entity* currentCamera;

	static uint32_t Fbo;
	void* textureId;
	bool canUpdate;

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
