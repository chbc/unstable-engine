#pragma once

#include <memory>
#include <string>
#include <cstdio>

namespace sre
{

namespace StringUtils
{
    template<typename ... Args>
    std::string format(const std::string& format, Args ... args)
    {
        size_t size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }
} // namespace

}
