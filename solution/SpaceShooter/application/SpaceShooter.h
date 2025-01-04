#pragma once
#include <RenderEngine.h>

using namespace sre;

class SpaceShooter : public RenderEngine
{
public:
	SpaceShooter();

protected:
	void onInit();
	void onUpdate(unsigned int elapsedTime);
};
