#pragma once

#include "CameraComponent.h"

namespace sre
{

class FlyingCameraComponent : public CameraComponent
{
DECLARE_COMPONENT()

private:
	glm::vec3 moveDirection;
	float yaw{ 0.0f };
	float pitch{ 0.0f };
	float moveSpeed{ 10.0f };

public:
	FlyingCameraComponent(Entity* entity);

protected:
    void onUpdate(float elapsedTime) override;

private:
	void processKeys();
	void processMouseMotion(float elapsedTime);
	void processMouseWheel(float elapsedTime);
	void updateMovement(float elapsedTime);
};

} // namespace
