#pragma once

#include "CameraComponent.h"

namespace sre
{

class FlyingCameraComponent : public CameraComponent
{
DECLARE_COMPONENT()

private:
	glm::vec3 moveDirection;
	glm::vec3 rotateDirection;
	glm::ivec2 lastMousePosition;

public:
	FlyingCameraComponent(Entity* entity);

protected:
    void onUpdate(uint32_t elapsedTime) override;

private:
	void processKeys();
	void processMouseMotion(uint32_t elapsedTime);
	void updateMovement(uint32_t elapsedTime);
};

} // namespace