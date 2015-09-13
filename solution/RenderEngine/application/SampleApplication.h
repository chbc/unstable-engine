#ifndef _SAMPLE_APPLICATION_H_
#define _SAMPLE_APPLICATION_H_

#include <engine/RenderEngine.h>

/*!
	Concrete application class.
*/
class SampleApplication : public RenderEngine
{
	private:
		float cubeAngle;
		RenderableNode *cube;

	protected:
		void onInit();
		void onUpdate(unsigned int elapsedTime);

		public:
			SampleApplication();
};

#endif
