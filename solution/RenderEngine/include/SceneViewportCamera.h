#pragma once

#include "memory_aliases.h"

#include <glm/mat4x4.hpp>
#include "glm/vec2.hpp"

namespace sre
{

enum class EViewingState
{
	NONE,
	FLYING,
	ORBIT,
	PAN
};

class SceneViewportCamera
{
private:
	class TransformComponent* cameraTransform{ nullptr };
	class CameraComponent* cameraComponent{ nullptr };
	class FlyingMovementComponent* flyingComponent{ nullptr };
	class OrbitMovementComponent* orbitComponent{ nullptr };
	class PanMovementComponent* panComponent{ nullptr };
	class MultimediaManager* multimediaManager{ nullptr };
	EViewingState viewingState{ EViewingState::NONE };
	float currentWindowWidth{ 0.0f };
	float currentWindowHeight{ 0.0f };
	glm::ivec2 initialMousePosition{ 0 };

public:
	void onInit();
	void onUpdate(float elapsedTime);
	void updateCameraPerspective(float newWidth, float newHeight);
	void getCameraMatrices(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);
	inline bool isCameraMoving() { return this->viewingState != EViewingState::NONE; };
	inline CameraComponent* getCameraComponent() { return this->cameraComponent; };
	void setCameraFocus(const glm::vec3& newTarget);

private:
	void updateViewingState();
	void processCameraMovement(float elapsedTime);
	void processMouseWheel(float elapsedTime);
	void updateInitialMousePosition();
	void forceInitialMousePosition();
};

} // namespace
