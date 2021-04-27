#include "BaseMessage.h"

namespace sre
{

uint16_t BaseMessage::Index = 0;

uint16_t BaseMessage::generateId()
{
	return Index++;
}


} // namespace
