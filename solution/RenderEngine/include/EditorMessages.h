#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "BaseMessage.h"

namespace sre
{

struct EntitySelectionMessage : public BaseMessage
{
	DECLARE_MESSAGE()

public:
	class Entity* entity;

	EntitySelectionMessage(class Entity* arg_entity) : entity(arg_entity) {}
};

struct ExitEditorMessage : public BaseMessage
{
	DECLARE_MESSAGE()
};

} // namespace

#endif
