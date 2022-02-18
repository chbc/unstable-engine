#pragma once

#include "CameraComponent.h"

namespace sre
{

class OrbitCameraComponent : public CameraComponent
{
	DECLARE_COMPONENT()

private:
	float targetDistance;

public:
	OrbitCameraComponent(Entity* entity);

protected:
	void onStart() override;
	void onUpdate(uint32_t deltaTime) override;

private:
	void processMouseWheel();
	void processMouseMotion();
};

} // namespace
