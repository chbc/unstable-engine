#pragma once

#include "IEditorWindow.h"
#include "Texture.h"
#include "memory_aliases.h"

#include "glm/vec2.hpp"

namespace sre
{

enum class EViewingState
{
	NONE,
	FLYING,
	ORBIT
};

class EditorsController;

class EditorSceneViewport : public IEditorWindow
{
private:
	class RenderManager* renderManager{ nullptr };
	SPTR<class Entity> camera{ nullptr };
	
	class FlyingMovementComponent* flyingComponent{ nullptr };
	class OrbitMovementComponent* orbitComponent{ nullptr };
	class MultimediaManager* multimediaManager{ nullptr };
	glm::ivec2 initialMousePosition{ 0 };
	EditorsController* controller{ nullptr };
	float currentWindowWidth{ 0.0f };
	float currentWindowHeight{ 0.0f };
	static uint32_t Fbo;
	uint64_t textureId{ 0 };
	bool canUpdate{ false };
	EViewingState viewingState{ EViewingState::NONE };

public:
	EditorSceneViewport(EditorsController* arg_controller);

	void onInit() override;
	void onUpdate(float elapsedTime) override;
	void onEditorGUI() override;
	void onRelease() override;

private:
	void handleFileDrop();
	void updateViewingState();
	void processCameraMovement(float elapsedTime);
	void processMouseWheel(float elapsedTime);
	void updateInitialMousePosition();
	void forceInitialMousePosition();
	void updateCameraPerspective(float newWidth, float newHeight);

friend class WorldEditor;
};

} // namespace
