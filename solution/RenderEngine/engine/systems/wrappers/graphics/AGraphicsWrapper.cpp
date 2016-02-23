#include "AGraphicsWrapper.h"
#include "OpenGLAPI.h"

AGraphicsWrapper *AGraphicsWrapper::getInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<AGraphicsWrapper>{ new OpenGLAPI{} };

	return instance.get();
}
