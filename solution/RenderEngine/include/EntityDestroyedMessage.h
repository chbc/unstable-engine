#pragma once

#include "BaseMessage.h"

namespace sre
{

struct EntityDestroyedMessage : public BaseMessage
{
	DECLARE_MESSAGE()
};

} // namespace
