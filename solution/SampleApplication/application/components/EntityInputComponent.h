#pragma once

#include "AEntityComponent.h"

using namespace sre;

class EntityInputComponent : public AEntityComponent
{
	DECLARE_COMPONENT()

private:
	const float IMPULSE{ 2.5f };
	const float GRAVITY{ 9.8f };
	float jumpSpeed{ 0.0f };

public:
	EntityInputComponent(Entity* entity);

protected:
	void onUpdate(float elapsedTime) override;
};
