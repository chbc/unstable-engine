#pragma once
#include <RenderEngine.h>
#include "ScreenManager.h"

using namespace sre;

/*!
	Concrete application class.
*/
class SampleApplication : public RenderEngine
{
private:
	ScreenManager screenManager;
	glm::vec2 direction;
	
public:
	SampleApplication();

protected:
	void onInit();
	void onUpdate(unsigned int elapsedTime);
};
