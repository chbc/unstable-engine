#pragma once

#include <stdint.h>

#define DECLARE_MESSAGE() \
    public: \
        static const uint16_t ID;

#define IMPLEMENT_MESSAGE(ClassName) \
    const uint16_t ClassName::ID = sre::BaseMessage::generateId();

namespace sre
{

struct BaseMessage
{
private:
    static uint16_t Index;

protected:
    static uint16_t generateId();
};

} // namespace
