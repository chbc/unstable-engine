#pragma once

#include "BaseMessage.h"

namespace sre
{

struct SRE_API EntityDestroyedMessage : public BaseMessage
{
	DECLARE_MESSAGE()
};

} // namespace
