#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "BaseMessage.h"

namespace sre
{

struct XXX_Message : public BaseMessage
{
	DECLARE_MESSAGE()
	int a;
};

} // namespace

#endif
