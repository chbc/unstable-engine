#ifndef _AGRAPHICS_WRAPPER_H_
#define _AGRAPHICS_WRAPPER_H_

#include <memory>

class AGraphicsWrapper
{
private:
	static std::unique_ptr<AGraphicsWrapper> instance;

protected:
	AGraphicsWrapper() {}

public:
	static AGraphicsWrapper *getInstance();
};

#endif
