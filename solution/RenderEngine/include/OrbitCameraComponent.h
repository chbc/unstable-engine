#pragma once

#include "CameraComponent.h"

namespace sre
{

class OrbitCameraComponent : public CameraComponent
{
	DECLARE_COMPONENT()

private:
	glm::vec3 target;

public:
	OrbitCameraComponent(Entity* entity);

protected:
	void onUpdate(float elapsedTime) override;

private:
	void processMouseMotion(float elapsedTime);
};

} // namespace
