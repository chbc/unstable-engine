#ifndef _SAMPLE_APPLICATION_H_
#define _SAMPLE_APPLICATION_H_

#include <RenderEngine.h>

using namespace sre;

class SampleApplication : public RenderEngine
{
private:
	Entity* entity;
	
public:
	SampleApplication();

protected:
	void onInit();
	void onUpdate(unsigned int elapsedTime);
};

#endif
