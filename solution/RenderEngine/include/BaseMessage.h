#pragma once

#include "core_defines.h"

#include <stdint.h>
#include <functional>

#define DECLARE_MESSAGE() \
    public: \
        static const uint16_t ID;

#define IMPLEMENT_MESSAGE(ClassName) \
    const uint16_t ClassName::ID = sre::BaseMessage::generateId();

namespace sre
{

using Action = std::function<void(void*)>;

struct SRE_API BaseMessage
{
private:
    static uint16_t Index;

protected:
    static uint16_t generateId();
};

} // namespace
