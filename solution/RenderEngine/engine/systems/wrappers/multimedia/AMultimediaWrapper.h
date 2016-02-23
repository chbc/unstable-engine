#ifndef _AMULTIMEDIA_WRAPPER_H_
#define _AMULTIMEDIA_WRAPPER_H_

#include <memory>

class AMultimediaWrapper
{
private:
	static std::unique_ptr<AMultimediaWrapper> instance;

protected:
	AMultimediaWrapper() {}

public:
	static AMultimediaWrapper *getInstance();
};

#endif
