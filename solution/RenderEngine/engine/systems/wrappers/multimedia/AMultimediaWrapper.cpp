#include "AMultimediaWrapper.h"

#include "SDLAPI.h"

namespace sre
{

AMultimediaWrapper *AMultimediaWrapper::getInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<AMultimediaWrapper>{ new SDLAPI{} };

	return instance.get();
}

} // namespace sre
