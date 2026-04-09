#pragma once

#include "AEntityComponent.h"

using namespace sre;

class TestChildComponent : public AEntityComponent
{
	DECLARE_COMPONENT()

public:
	TestChildComponent(Entity* entity);

protected:
	void onInit() override;
};
