#pragma once

#include "AEntityComponent.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sre
{

class SRE_API FlyingMovementComponent : public AEntityComponent
{
DECLARE_COMPONENT()

private:
	float moveSpeed{ 10.0f };
	const float WHEEL_RATE = 30.0f;

public:
	FlyingMovementComponent(Entity* entity);
	void processMovement(const glm::vec3& moveDirection, const glm::vec2& mouseDelta, float elapsedTime);
	void addSpeed(float mouseWheel, float elapsedTime);

private:
	void updateOrientation(const glm::vec2& mouseDelta, float elapsedTime);
	void updateMovement(const glm::vec3& moveDirection, float elapsedTime);
};

} // namespace
