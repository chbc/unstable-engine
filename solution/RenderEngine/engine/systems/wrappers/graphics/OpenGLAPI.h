#ifndef _OPENGL_API_H_
#define _OPENGL_API_H_

class AGraphicsWrapper;

class OpenGLAPI : AGraphicsWrapper
{
protected:
	OpenGLAPI() {}

public:

	friend class AGraphicsWrapper;
};

#endif
