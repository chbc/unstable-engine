#ifndef _SDLAPI_H_
#define _SDLAPI_H_

class AMultimediaWrapper;

class SDLAPI : AMultimediaWrapper
{
protected:
	SDLAPI() {}

	friend class AMultimediaWrapper;
};

#endif
