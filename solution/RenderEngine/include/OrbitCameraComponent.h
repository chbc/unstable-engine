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
	void onInit() override;
	void onUpdate(float elapsedTime) override;

private:
	void processMouseMotion(float elapsedTime);
};

} // namespace
