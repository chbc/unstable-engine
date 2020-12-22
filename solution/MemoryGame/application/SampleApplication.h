#ifndef _SAMPLE_APPLICATION_H_
#define _SAMPLE_APPLICATION_H_

#include <RenderEngine.h>

using namespace sre;

/*!
	Concrete application class.
*/
class SampleApplication : public RenderEngine
{
private:
	Entity* entity;
	glm::vec2 direction;
	
public:
	SampleApplication();

protected:
	void onInit();
	void onUpdate(unsigned int elapsedTime);
};

#endif
