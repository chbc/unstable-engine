#include "AMultimediaWrapper.h"

#include "SDLAPI.h"

AMultimediaWrapper *AMultimediaWrapper::getInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<AMultimediaWrapper>{ new SDLAPI{} };

	return instance.get();
}
