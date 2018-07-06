#ifndef _SAMPLE_APPLICATION_H_
#define _SAMPLE_APPLICATION_H_

#include <engine/RenderEngine.h>

using namespace sre;

/*!
	Concrete application class.
*/
class SampleApplication : public RenderEngine
{
public:
	SampleApplication();

protected:
	void onInit();
	void onUpdate(unsigned int elapsedTime);

private:
    void createRoom();
};

#endif
