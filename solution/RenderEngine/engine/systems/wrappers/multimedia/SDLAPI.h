#ifndef _SDLAPI_H_
#define _SDLAPI_H_

namespace sre
{

class AMultimediaWrapper;

class SDLAPI : AMultimediaWrapper
{
	protected:
		SDLAPI() {}

		friend class AMultimediaWrapper;
};

} // namespace sre
#endif
