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
	void onInit() override;
	void onUpdate(float elapsedTime) override;

private:
	void createLights();

	void processMouse();
};

#endif
