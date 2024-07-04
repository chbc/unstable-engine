#ifndef _SAMPLE_APPLICATION_H_
#define _SAMPLE_APPLICATION_H_

#include <RenderEngine.h>

using namespace sre;

/*!
	Material Combinations Example
*/
class SampleApplication : public RenderEngine
{
private:
	class CameraComponent* camera;

public:
	SampleApplication();

protected:
	void onInit();
	void onUpdate(unsigned int elapsedTime);

private:
	void createLights();

	void processKeys();
	void processMouse();
};

#endif
