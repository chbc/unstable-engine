#ifndef _SAMPLE_APPLICATION_H_
#define _SAMPLE_APPLICATION_H_

#include <RenderEngine.h>

using namespace sre;

class SampleApplication : public RenderEngine
{
private:
	float time = 0;
	int indice = 0;

public:
	SampleApplication();

protected:
	void onInit() override;
	void onUpdate(float elapsedTime) override;
};

#endif
