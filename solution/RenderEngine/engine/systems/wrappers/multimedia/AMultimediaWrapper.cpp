#include "AMultimediaWrapper.h"

#include "SDLAPI.h"

namespace sre
{

std::unique_ptr<AMultimediaWrapper> AMultimediaWrapper::instance{ nullptr };

AMultimediaWrapper *AMultimediaWrapper::getInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<AMultimediaWrapper>{ new SDLAPI{} };

	return instance.get();
}

} // namespace sre
