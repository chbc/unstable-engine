#pragma once

#include "BaseMessage.h"

#include <vector>

namespace sre
{

class Entity;
class AEntityComponent;

struct SRE_API EnqueueEntityToDestroyMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	Entity* entity{ nullptr };

public:
	EnqueueEntityToDestroyMessage(Entity* arg_entity) : entity(arg_entity) {}
};

struct SRE_API EnqueueComponentToDestroyMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	AEntityComponent* component{ nullptr };

public:
	EnqueueComponentToDestroyMessage(AEntityComponent* arg_component) : component(arg_component) {}
};

} // namespace
