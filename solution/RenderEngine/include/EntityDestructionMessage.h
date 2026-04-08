#pragma once

#include "BaseMessage.h"

#include <vector>

namespace sre
{

class Entity;

struct SRE_API EnqueueEntityToDestroyMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	Entity* entity{ nullptr };

public:
	EnqueueEntityToDestroyMessage(Entity* arg_entity) : entity(arg_entity) {}
};

struct SRE_API EntityDestroyedMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	Entity* entity;

public:
	EntityDestroyedMessage(Entity* arg_entity) : entity(arg_entity) {}
};

} // namespace
