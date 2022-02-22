#pragma once

#include "CameraComponent.h"

namespace sre
{

class OrbitCameraComponent : public CameraComponent
{
	DECLARE_COMPONENT()

public:
	OrbitCameraComponent(Entity* entity);

protected:
	void onStart() override;
	void onUpdate(uint32_t elapsedTime) override;

private:
	void processMouseMotion(uint32_t elapsedTime);
};

} // namespace
