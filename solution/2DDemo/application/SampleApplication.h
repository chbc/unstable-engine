#ifndef _SAMPLE_APPLICATION_H_
#define _SAMPLE_APPLICATION_H_

#include <RenderEngine.h>

using namespace sre;

class SampleApplication : public RenderEngine
{
public:
	SampleApplication();

protected:
	void onInit() override;
};

#endif
