#pragma once

#include "BaseMessage.h"

namespace sre
{

class Entity;

struct SRE_API EntityDestroyedMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	Entity* entity{ nullptr };

public:
	EntityDestroyedMessage(Entity* arg_entity) : entity(arg_entity) {}
};

} // namespace
