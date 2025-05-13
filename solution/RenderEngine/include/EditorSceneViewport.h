#pragma once

#include "IEditorWindow.h"
#include "Texture.h"
#include "memory_aliases.h"

#include "glm/vec2.hpp"

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
	class MultimediaManager* multimediaManager{ nullptr };
	glm::ivec2 initialMousePosition;

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
	void updateInitialMousePosition();
	void forceInitialMousePosition();

friend class WorldEditor;
};

} // namespace
