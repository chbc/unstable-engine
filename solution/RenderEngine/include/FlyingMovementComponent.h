#pragma once

#include "AEntityComponent.h"

#include <glm/vec3.hpp>

namespace sre
{

class SRE_API FlyingMovementComponent : public AEntityComponent
{
DECLARE_COMPONENT()

private:
	float yaw{ 0.0f };
	float pitch{ 0.0f };
	float moveSpeed{ 10.0f };

public:
	FlyingMovementComponent(Entity* entity);
	void processMovement(const glm::vec3& moveDirection, const glm::vec2& mouseDelta, float elapsedTime);
	void addSpeed(float mouseWheel, float elapsedTime);

private:
	void updateOrientation(const glm::vec2& mouseDelta, float elapsedTime);
	void updateMovement(const glm::vec3& moveDirection, float elapsedTime);
};

} // namespace
